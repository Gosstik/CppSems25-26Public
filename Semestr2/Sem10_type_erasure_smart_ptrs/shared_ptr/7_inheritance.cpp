#include <memory>

// In ControlBlock we have to store U, but in shared_ptr we will store T

// static_pointer_cast

struct Base {};

struct PrivateParent : Base {};

int main() {
    auto p = std::make_shared<PrivateParent>();
    std::shared_ptr<Base> bp = p;  // OK, but we do not have that ctor yet
}
