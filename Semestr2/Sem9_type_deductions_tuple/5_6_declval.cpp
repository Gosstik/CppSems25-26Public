#include <utility>

class MyType {
    // MyType() = delete;
    MyType() {};

  public:
    int GetVal() { return 0; }
};

template <typename T>
void Foo() {
    // decltype(T().GetVal()) g1;
    decltype(std::declval<T>().GetVal()) g2;
}

int main() {
    int x = 0;
    decltype(x) y = 1;
    Foo<MyType>();

    int a = std::declval<int>(); // CE
}
