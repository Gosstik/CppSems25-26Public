#include <iostream>

// TODO: make overload by return type

template <typename T, typename U>
struct A {
    template <typename TT>
    struct Type2Type {
        using Type = TT;
    };

    void Foo() { Fimpl(Type2Type<T>{}); }

  private:
    template <typename V>
    void Fimpl(V) {
        std::cout << "other\n";
    }

    void Fimpl(Type2Type<int>) { std::cout << "int\n"; }
};

int main() {
    A<int, double> a;
    A<float, double> b;

    // ! Different version without specializing struct
    a.Foo();  // int version
    b.Foo();  // other version
}
