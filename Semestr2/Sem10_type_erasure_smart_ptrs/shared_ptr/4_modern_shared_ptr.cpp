#include <cstddef>
#include <utility>

//// Discuss
// size_t count
// static size_t count
// size_t* count

// Save bool in last bit of count_ whether we were created from ControlBlock or
// from ptr

template <typename T>
class SharedPtr {
  private:
    struct ControlBlockBase {
        size_t shared_count;
        size_t weak_count;
    };

    struct ControlBlockMakeShared : ControlBlockBase {
        T value;
    };

    // TODO: do we need U ???
    template <typename U, typename... Args>
    friend SharedPtr<U> MakeShared(Args&&...);

    SharedPtr(ControlBlockMakeShared* block) {}  // TODO

  public:
    SharedPtr(T* ptr) : ptr_(ptr), block_(new ControlBlockBase{1, 0}) {}

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), block_(other.block_) {
        ++block_->shared_count;
    }

    ~SharedPtr() {
        if (block_->shared_count == 0) {  // TODO: do we need it ???
            return;
        }
        --block_->shared_count;
        if (block_->shared_count == 0) {
            // delete count_; // WRONG now
            delete ptr_;
        }
    }

  private:
    T* ptr_;
    ControlBlockBase* block_;
};

////////////////////////////////////////////////////////////////////////////////

// MakeShared (since c++11)

// To avoid double call to operator new

template <typename T, typename... Args>
SharedPtr<T> MakeShared(Args&&... args) {
    auto* p = new SharedPtr<T>::ControlBlockMakeShared{
        T(std::forward<Args>(args)...), 1};
    return SharedPtr<T>(p);
}

////////////////////////////////////////////////////////////////////////////////

int main() {}
