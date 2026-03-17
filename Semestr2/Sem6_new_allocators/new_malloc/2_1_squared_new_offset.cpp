#include <new>

// Use ASan

struct A {
    ~A() {}            // without it ASan cannot catch error
    int* x = nullptr;  // sizeof(A) == 8
};

int main() {
    // OK
    // A* a = reinterpret_cast<A*>(new char[sizeof(A)]);
    // new (a) A();

    // not OK, but why???
    A* a = new A[1];

    // delete[] a;
    a[0].~A();
    operator delete[](a - 1);  //* delete[] adds offset to operator delete[]
}

// new int[]
//   1 2 3 4

// new A[]
// 4 A() A() A() A()
// |
