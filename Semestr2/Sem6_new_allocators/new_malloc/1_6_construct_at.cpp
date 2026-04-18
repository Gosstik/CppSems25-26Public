#include <iostream>
#include <memory>    // std::construct_at, std::destroy_at

// Reasons to use std::construct_at
// 1) std::construct_at is constexpr since c++20, but placement new since c++26
// 2) Symmetry with std::destroy_at

class MyClass {
public:
    MyClass(int x, double y)
        : x_(x), y_(y)
    {
        std::cout << "Constructor: x=" << x_ << ", y=" << y_ << "\n";
    }

    ~MyClass() {
        std::cout << "Destructor: x=" << x_ << ", y=" << y_ << "\n";
    }

    void Print() const {
        std::cout << "print(): x=" << x_ << ", y=" << y_ << "\n";
    }

private:
    int x_;
    double y_;
};

int main() {
    // Step 1: Allocate raw memory (no constructor called)
    char buffer[sizeof(MyClass)]; // !!! alignas is required

    std::cout << "--- Memory allocated, no object yet ---\n";

    // Step 2: Construct object in that memory
    // MyClass* obj2 = new(buffer) MyClass(42, 3.14); // same as construct_at
    MyClass* obj = std::construct_at(
        reinterpret_cast<MyClass*>(buffer),
        42,     // x
        3.14    // y
    );

    std::cout << "--- Object constructed ---\n";

    obj->Print();

    // Step 3: Destroy object (calls destructor, does NOT free memory)
    std::destroy_at(obj);

    std::cout << "--- Object destroyed, memory still exists ---\n";

    // buffer[] is stack memory — automatically reclaimed when main() returns
}
