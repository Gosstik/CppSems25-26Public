#include <memory>

// Smart pointers represent RAII in c++ (e.g. to avoid memory leaks)

template <typename T>
struct DefaultDelete {
    void operator()(T* ptr) const { delete ptr; }
};

template <typename T, typename Deleter = std::default_delete<T>>
class UniquePtr {
  public:
    explicit UniquePtr(T* ptr) noexcept : ptr_(ptr) {}
    ~UniquePtr() { deleter_(ptr_); }
    UniquePtr(T* ptr, Deleter deleter) : ptr_(ptr), deleter_(deleter) {}
    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    UniquePtr(UniquePtr&& other) noexcept
        : ptr_(other.ptr_),
          deleter_(std::move(other.deleter_)) {
        other.ptr_ = nullptr;
    }
    UniquePtr& operator=(UniquePtr&& other) noexcept {
        if (this == &other) {
            return *this;
        }
        deleter_(ptr_);
        ptr_ = other.ptr_;
        other.ptr_ = nullptr;
        deleter_ = std::move(other.deleter_);
        return *this;
    }

    // actually std::add_lvalue_reference_t<T> to support UniquePtr<void>
    T& operator*() const { return *ptr_; }

    T* operator->() const { return ptr_; }

    T* Get() const { return ptr_; }

    // Reset

  private:
    T* ptr_;
    [[no_unique_address]] Deleter deleter_;
};

////////////////////////////////////////////////////////////////////////////////

// MakeUnique (since c++14)

// A way to avoid creating two UniquePtrs from the same pointer

template <typename T, typename... Args>
UniquePtr<T> MakeUnique(Args&&... args) {
    return UniquePtr<T>(new T(std::forward<Args>(args)...));
}

////////////////////////////////////////////////////////////////////////////////

void Foo(...) {}

int Bar() { throw 1; }

int main() {
    // Foo(UniquePtr<int>(new int(5)), Bar()); // Problem until c++17
}
