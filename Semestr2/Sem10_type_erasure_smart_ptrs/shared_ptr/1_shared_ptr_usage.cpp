#include <memory>

// Create two shared pointers on one pointer --- UB

int main() {
    auto p1 = std::shared_ptr<int>(new int(5));  // NOLINT
    auto p2 = p1;
    auto p3 = p1;

    p2 = std::shared_ptr<int>(new int(8));  // NOLINT
    auto p4 = std::move(p1);  // p1 -> nullptr, p2 -> 8, p3, p4 -> 5
    p4.reset();               // p1, p4 -> nullptr, p2 -> 8, p3 -> 5

    auto mp1 = std::make_shared<int>(5);

    static_assert(sizeof(std::shared_ptr<int>) == 16);
}
