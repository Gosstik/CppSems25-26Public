#include <vector>
#include <array>

// https://en.cppreference.com/w/cpp/container/stack.html

// template<
//     class T,
//     class Container = std::deque<T>
// > class stack;

// Requires from container:
// - push_back(value)
// - pop_back()
// - back()
// - size()
// - empty()
// - ...

// ??? Why std::deque is used as default container?

template <template<typename, typename...> typename Container, typename DefaultT = int>
void Foo(Container<DefaultT>& c) {
    // ...
}

template <template<typename, size_t> typename Container, typename DefaultT = int>
void Foo(Container<DefaultT, 10>& c) {
    // ...
}

int main() {
    std::vector<int> v;
    Foo(v); // CE

    std::array<int, 10> a;
    Foo(a); // CE
}
