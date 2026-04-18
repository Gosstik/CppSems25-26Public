#include <iostream>
#include <vector>

// std::pmr::vector = std::vector<T, std::pmr::polymorphic_allocator<T>>

int main() {
    std::pmr::vector<int> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    std::cout << vec.size() << '\n';
}
