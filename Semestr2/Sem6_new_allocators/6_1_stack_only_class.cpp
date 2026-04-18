#include <iostream>

struct A {
  public:
    void* operator new(size_t n) = delete;
    void operator delete(void* ptr) = delete;
};

int main() {
    A* pa = new A{};  // CE
    A* pa2 = ::new A{};  // OK

    // ???

    A a;
}
