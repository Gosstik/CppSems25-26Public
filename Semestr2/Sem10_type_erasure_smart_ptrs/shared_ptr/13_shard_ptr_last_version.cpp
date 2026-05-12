#include <cstddef>
#include <iostream>
#include <memory>
#include <optional>

template <typename T>
class SharedPtr;

template <typename T>
struct EnableSharedFromThis;

template <typename T>
class WeakPtr {
  public:
    template <typename U>
    friend class SharedPtr;

    WeakPtr() = default;
    WeakPtr(const SharedPtr<T>& ptr) : sp_(&ptr) { ++sp_->cb_->count_weak_; }

    // lock()
    // expired()
    ~WeakPtr() {
        // --weak_counter
        // if weak_counter == 0 && chared_coutner_ == 0 => delete cb_
    }

    SharedPtr<T> Lock() { return *sp_; }

  private:
    SharedPtr<T>* sp_;
};

// Type Erasure

template <typename T>
class SharedPtr {
  public:
    template <typename U>
    friend class WeakPtr;

    struct ControlBlock {
        ControlBlock(size_t n) : count_shared_(n) {}
        virtual ~ControlBlock() { std::cout << "~ControlBlock()" << std::endl; }

        virtual void ClearT() = 0;
        virtual void DeleteSelf() = 0;

        // virtual auto GetAlloc() = 0;

        size_t count_shared_;
        size_t count_weak_ = 0;
    };

    //// Creation of shared_ptr with make_shared
    template <typename Alloc = std::allocator<T>>
    struct ControlBlockWithT : public ControlBlock {
        // T ptr_; // !!! connot be destructed in ControlBlockWithT
        // std::aligned_storage_t<sizeof(T), alignof(T)> ptr_; // #include
        // <type_traits>
        std::optional<T> ptr_;  // #include <optional>
        Alloc alloc_;

        template <typename... Args>
        ControlBlockWithT(size_t n, Args&&... args)
            : ControlBlock(n),
              ptr_(std::forward<Args>(args)...) {}

        void ClearT() override { ptr_ = std::nullopt; }

        void DeleteSelf() override {
            auto alloc = alloc_;
            // delete this;
            // TODO: rebind_alloc or define other allocator in fields
            std::allocator_traits<Alloc>::destroy(&alloc, *this);
            std::allocator_traits<Alloc>::deallocate(&alloc, this, 1);
        }

        // TODO: ctor for alloc
    };

    //// Creation of shared_ptr from pointer
    template <
        typename Deleter = std::default_delete<T>,
        typename Alloc = std::allocator<T>>
    struct ControlBlockSimple : public ControlBlock {
        [[no_unique_address]] Deleter deleter_;
        [[no_unique_address]] Alloc
            alloc_;  // stores passed to shared_apt alloc

        ControlBlockSimple(Deleter d, Alloc a)
            : ControlBlock(1),
              deleter_(d),
              alloc_(a) {}

        void ClearT() override { deleter_(ptr_); }

        // TODO: ctor for alloc
    };

    SharedPtr() = default;

    template <typename Alloc, typename Deleter>
    SharedPtr(
        T* ptr,
        Deleter d = std::default_delete<T>{},
        Alloc alloc = std::allocator<T>{})
        : ptr_(ptr),
          // cb_(new ControlBlockSimple(d, alloc)) // !!! use alloc instead of
          // new
          cb_(nullptr) {
        using BlockType = ControlBlockSimple<Deleter, Alloc>;
        using AllocTraits = std::allocator_traits<Alloc>;
        using BlockAllocTraits = AllocTraits::template rebind_traits<BlockType>;

        cb_ = BlockAllocTraits::allocate(alloc, sizeof(BlockType));
        BlockAllocTraits::construct(alloc, cb_, d, alloc);

        std::cout << "SharedPtr(ptr)" << std::endl;
        if constexpr (std::is_base_of_v<EnableSharedFromThis<T>, T>) {
            ptr_->wp_.sp_ = this;
        }
    }

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), cb_(other.cb_) {
        if (ptr_) {
            ++cb_->count_shared_;
        }
        std::cout << "SharedPtr(const SharedPtr&)" << std::endl;
    }

    SharedPtr(SharedPtr&& other) : ptr_(other.ptr_), cb_(other.cb_) {
        other.ptr_ = nullptr;
        other.cb_ = nullptr;
    }

    template <typename Alloc>
    SharedPtr(ControlBlockWithT<Alloc>* cb) : ptr_(&cb->ptr_),
                                              cb_(cb) {
        std::cout << "SharedPtr(ControlBlockWithT)" << std::endl;
    }
    SharedPtr& operator=(const SharedPtr& other) {
        std::cout << "operator=(const SharedPtr&)" << std::endl;
        if (this == &other) {
            return *this;
        }
        Reset();
        ptr_ = other.ptr_;
        cb_ = other.cb_;
        ++cb_->count_shared_;
        return *this;
    }

    void Reset() {
        // Case for default ctor
        if (ptr_ == nullptr) {
            return;
        }
        // TODO: cb
        // auto cbt = dynamic_cast<ControlBlockWithT*>(cb_);
        --cb_->count_shared_;
        if (cb_->count_shared_ == 0) {
            if (cb_->count_weak_ == 0) {
                cb_->ClearT();
                // !!! instead of dynamic_cast
                // if (cbt) {
                //   delete cbt;
                //   return;
                // }
                delete ptr_;
                delete cb_;
            } else {
                // ~T()
                ptr_->~T();
            }
        }
    }

    ~SharedPtr() {
        std::cout << "~SharedPtr()" << std::endl;
        Reset();
    }

    //  private:
    T* ptr_ = nullptr;
    ControlBlock* cb_ = nullptr;
};

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    return {
        new SharedPtr<T>::ControlBlockWithT(1, std::forward<Args>(args)...)};
}

// AllocateShared

SharedPtr<int> Foo() {
    int* p = new int(10);
    SharedPtr<int> s1(p);
    SharedPtr<int> s2(s1);
    return s2;
}

template <typename T>
struct EnableSharedFromThis {
    EnableSharedFromThis() = default;

    SharedPtr<T> SharedFormThis() { return wp_.Lock(); }

    template <typename U>
    friend class SharedPtr;

  private:
    WeakPtr<T> wp_;
};

// CRTP
struct My : public EnableSharedFromThis<My> {
    SharedPtr<My> GetShared() {
        // return {this};  // double free
        return SharedFormThis();  // std::bad_weak_ptr
    }
};

void Foo(My& m) {
    // SharedPtr m
    m.GetShared();
}

struct Base {
    virtual ~Base() = default;
};

struct Derived : Base {};

int main() {
    // SharedPtr<My> sp(new My());

    // SharedPtr<My> sp2 = sp.ptr_->GetShared();
    // auto sp3 = sp.ptr_->GetShared();

    SharedPtr<Base> sp = new Derived();
    SharedPtr<Derived> spd(sp);

    //// class example
    // std::shared_ptr<My> sp1; // default, sp1 stores nullptr
    // std::shared_ptr<My> sp2; // default, sp2 stores nullptr
    // sp1->val = sp2; // RE, no val in sp1
    // sp2->val = sp1; // RE, no val in sp2

    //// No leak
    // My* m1 = new My();
    // My* m2 = new My();
    // std::shared_ptr<My> sp1(m1);
    // std::shared_ptr<My> sp2(m2);
    // sp1->val = sp2;
    // sp2->val = sp1;
    // std::cout << sp1.use_count() << std::endl; // 2
    // std::cout << sp2.use_count() << std::endl; // 2

    //// No leak
    // My* m = new My();
    // std::shared_ptr<My> sp(m);
    // sp->val = sp;
    // std::cout << sp.use_count() << '\n'; // 2

    //// Leak
    // std::shared_ptr<My> sp1 = std::make_shared<My>(My());
    // std::shared_ptr<My> sp2 = std::make_shared<My>(My());
    // sp1->val = sp2;
    // sp2->val = sp1;
    // std::cout << sp1.use_count() << std::endl; // 2
    // std::cout << sp2.use_count() << std::endl; // 2

    //// Test our not leak
    // My2* m1 = new My2();
    // My2* m2 = new My2();
    // SharedPtr<My2> sp1(m1);
    // SharedPtr<My2> sp2(m2);
    // sp1.ptr_->val = sp2;
    // sp2.ptr_->val = sp1;
    // std::cout << sp1.cb_->count_ << std::endl; // 2
    // std::cout << sp2.cb_->count_ << std::endl; // 2

    //// Test our leak
    // My2* m1 = new My2();
    // My2* m2 = new My2();
    // SharedPtr<My2> sp1 = MakeShared<My2>();
    // std::cout << "???" << std::endl;
    // SharedPtr<My2> sp2 = MakeShared<My2>();
    // sp1.ptr_->val = sp2;
    // sp2.ptr_->val = sp1;
    // std::cout << sp1.cb_->count_shared_ << std::endl;  // 2
    // std::cout << sp2.cb_->count_shared_ << std::endl;  // 2

    // SharedPtr<My2> sp1;
    // sp1.ptr_->val = sp1;

    // My* m = new My();
    // std::shared_ptr<My> sp1(m);
    // sp1->val = sp1; // count = 2

    // SharedPtr<My2> sp2;
    // std::cout << sp2.cb_->count_ << ' ';
    // std::cout << sp1.cb_->count_ << '\n';
    // sp1.ptr_->val = sp2;
    // std::cout << sp2.cb_->count_ << ' ';
    // std::cout << sp1.cb_->count_ << '\n';
    // sp2.ptr_->val = sp1;
    // std::cout << sp2.cb_->count_ << ' ';
    // std::cout << sp1.cb_->count_ << std::endl;

    // Bar(std::make_shared(1), Throwable()); // under c++17 unspesified
}
