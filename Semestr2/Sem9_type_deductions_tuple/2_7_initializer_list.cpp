#include <initializer_list>

template <typename T>
void Foo(T) {}

template <typename T>
void Debug() = delete;

int main() {
    Foo({1, 2, 3});        // CE, couldn't infer template argument 'T'
    auto lst = {1, 2, 3};  // OK

    Debug<decltype(lst)>();  // T = std::initializer_list<int>
}
