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
    struct ControlBlockMakeShared {
        T value;
        size_t count;
    };

    // TODO: do we need U ???
    template <typename U, typename... Args>
    friend SharedPtr<U> MakeShared(Args&&...);

    SharedPtr(ControlBlockMakeShared* block) {}  // TODO

  public:
    SharedPtr(T* ptr) : ptr_(ptr), count_(new size_t(1)) {}

    SharedPtr(const SharedPtr& other) : ptr_(other.ptr_), count_(other.count_) {
        ++*count_;
    }

    ~SharedPtr() {
        if (count_ == 0) {  // TODO: do we need it ???
            return;
        }
        --*count_;
        if (*count_ == 0) {
            delete count_;
            delete ptr_;
        }
    }

  private:
    T* ptr_;
    size_t* count_;
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
