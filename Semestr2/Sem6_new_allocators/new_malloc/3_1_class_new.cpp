#include <iostream>

struct A {
    inline static int count = 0;

    void* operator new(size_t n) {  // static be default
        std::cout << "operator new for A\n";
        return malloc(n);
    }

    void operator delete(void* ptr, size_t) {  // static by default
        std::cout << "operator delete for A\n";
        free(ptr);
    }

    A() = default;

    void GlobalNew() {
        std::cout << "----Global New\n";

        int* val = ::new int(1);  // no need for ::
        std::cout << "&val: " << val << '\n';
        ::delete val;
    }

    void LocalNew() {
        std::cout << "----Local New\n";

        int* val = new int(1);  // will not call local operator new
        // int* val = A::new int(1); // CE: expected unqualified id
        // int* val = (int*)operator new(1);

        std::cout << "&val: " << val << '\n';

        delete val;
        // operator delete(val);
    }
};

int main() {
    A* pa = new A{}; // !!! here also class operator new will be used
    delete pa;

    A a;
    a.GlobalNew();
    a.LocalNew();
}
