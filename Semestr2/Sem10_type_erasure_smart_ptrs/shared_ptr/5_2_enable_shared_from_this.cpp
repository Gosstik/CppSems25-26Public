#include <memory>

template <typename T>
struct EnableSharedFromThis {
    std::shared_ptr<T> SharedFromThis() const { return wptr.lock(); }

    EnableSharedFromThis() = default;  // Edit shared_ptr ctor
  private:
    // can't store shared_ptr here --- it creates cycle on itself
    // std::shared_ptr<T> sptr;
    std::weak_ptr<T> wptr;
};

////////////////////////////////////////////////////////////////////////////////

// Inheritance must be public to access private members of EnableSharedFromThis
// in shared_ptr.

struct S : public std::enable_shared_from_this<S> {
    std::shared_ptr<S> GetShared() { return shared_from_this(); }
};

int main() {}
