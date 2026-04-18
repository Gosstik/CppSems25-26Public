#include <iostream>

// clang-format off

// Non-allocating placement allocation functions
// void* operator new  ( std::size_t count, void* ptr ); (9)
// void* operator new[]( std::size_t count, void* ptr ); (10)

// // The actual implementation in the standard library (not weak - we should not override it)
// void* operator new(std::size_t count, void* ptr) noexcept {
//     return ptr;  // Just returns ptr.
// }

struct MyClass {
    int value;
    MyClass(int v) : value(v) {
        std::cout << "MyClass(" << value << ") constructed\n";
    }
    ~MyClass() { std::cout << "~MyClass(" << value << ") destroyed\n"; }
};

int main() {
    // Allocate raw memory (no constructor called)
    char buffer[sizeof(MyClass)]; // !!! alignas is required
    // void* buffer = malloc(sizeof(MyClass));

    // !!! Still placement new, but we use just "new"
    // new expression always requires two steps:
    // 1) Call operator new - here we use Non-allocating placement allocation functions
    // 2) Call ctor on address
    MyClass* obj = new (buffer) MyClass(42);

    std::cout << "Value: " << obj->value << "\n";

    // Must call destructor MANUALLY (no delete!)
    obj->~MyClass();

    // Note: don't use "delete obj" - we didn't allocate with new!
}

// clang-format on
