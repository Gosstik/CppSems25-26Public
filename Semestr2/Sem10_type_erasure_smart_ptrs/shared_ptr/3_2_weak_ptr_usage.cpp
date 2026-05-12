#include <memory>

// Application: cyclic dependencies in trees

// Weak pointer has no operator*

// How to check that shared_ptr is expired? We can't check count because it is
// deleted in case ptr was expired.

// We will store shared count and weak count

int main() {
    auto p = std::make_shared<int>(5);

    std::weak_ptr<int> wp = p;
    if (!wp.expired()) {
        auto p2 = wp.lock();
    }
}
