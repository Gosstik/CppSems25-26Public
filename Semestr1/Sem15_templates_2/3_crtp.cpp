#include <iostream>

// CRTP - Curiously Reccurring Template Pattern

template <class T>
struct Base {
    // T d;    // CE (incomplete type)
    T* pd;  // OK
    T& rd;  // OK

    explicit Base(T& derived) : pd(*derived), rd(derived) {}

    void InterfaceFunc() {
        // ...
        static_cast<T*>(this)->FuncImpl();
        // ...
    }

    static void StaticFunc() {
        // ...
        T::DerivedStaticFunc();
    }
};

struct Derived : Base<Derived> {
    void FuncImpl() {};
    static void DerivedStaticFunc() { std::cout << "Derived!!!\n"; };
};

int main() {
    // Derived d;
    // d.InterfaceFunc();
}
