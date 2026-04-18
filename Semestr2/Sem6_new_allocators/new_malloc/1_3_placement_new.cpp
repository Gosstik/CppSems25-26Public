#include <iostream>

struct MyClass {
    int value;
    MyClass(int v) : value(v) {
        std::cout << "MyClass(" << value << ") constructed\n";
    }
    ~MyClass() { std::cout << "~MyClass(" << value << ") destroyed\n"; }
};

int main() {
    // Allocate raw memory (no constructor called)
    char buffer[sizeof(MyClass)];  // !!! alignas is required
    // void* buffer = malloc(sizeof(MyClass));

    // Placement new: construct object at specific address
    MyClass* obj = new (buffer) MyClass(42);

    std::cout << "Value: " << obj->value << "\n";

    // Must call destructor MANUALLY (no delete!)
    obj->~MyClass();

    // Note: don't use "delete obj" - we didn't allocate with new!
}
