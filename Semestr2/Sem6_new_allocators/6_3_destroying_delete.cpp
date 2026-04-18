#include <iostream>
#include <memory>
#include <new>

// https://stackoverflow.com/questions/67595789/what-is-destroying-operator-delete-in-c20
// https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2017/p0722r1.html

// void operator delete(void* pa) {
//     std::cout << "1: " << pa << '\n';
//     free(pa);
//     // delete pa;
//     // delete pa;
// }

struct A {
  public:
    A() = default;

    void* operator new(size_t n) {  // static by default
        std::cout << "operator new for A\n";
        return malloc(n);
    }

    // void operator delete(void* ptr) {  // static by default
    //     std::cout << "operator delete for A\n";
    //     free(ptr);
    // }

    // Must be a member function
    void operator delete(A* pa, std::destroying_delete_t) {
        pa->~A();  // !!! Is not called automatically by compiler
        std::cout << "2: " << pa << '\n';
        free(pa);
    }

    void Print() {  // NOLINT
        std::cout << "Print A\n";
    }

  private:
    ~A() { std::cout << "~A()\n"; }
};

int main() {
    // A a;  // CE

    A* pa = new A();
    pa->Print();
    // delete pa; // CE
    A::operator delete(pa, std::destroying_delete);
}
