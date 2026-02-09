#include <iostream>

struct S {
    int a = 1;

    void Func() {
        std::cout << a;
        delete this;

        std::cout << "Hello\n";  // OK
        std::cout << a << '\n';  // UB --- Heap Use After Free
    }
};

int main() {
    {
        // delete nullptr

        int* a = nullptr;
        delete a;  // OK
    }

    {
        // delete this

        S* s = new S();
        s->Func();
        // ...
    }
}
