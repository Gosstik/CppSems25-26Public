#include <array>
#include <memory_resource>
#include <vector>

std::pmr::vector<int> Foo() {
    static std::array<int, 1024> buf;
    static std::pmr::monotonic_buffer_resource mem_resource(
        &buf, buf.size() * sizeof(int), std::pmr::get_default_resource());
    return std::pmr::vector<int>{&mem_resource};
}

int main() {
    std::pmr::vector<int> v = Foo();

    std::pmr::vector<int> w;
    w = Foo();  // !!! memory resource will not be replaced
    // Default memory resource will be used, because it was set on vector
    // default construction
}
