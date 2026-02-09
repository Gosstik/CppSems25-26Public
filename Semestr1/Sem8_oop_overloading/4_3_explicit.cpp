#include <iostream>

struct Latitude {
    double val;
    explicit Latitude(double val) : val(val) {}

    explicit operator double() const { return val; }
};

// contextual conversion --- inside if
// implicit conversion --- in other cases

struct PointerWrapper {
    int* ptr;
    explicit PointerWrapper(int* ptr) : ptr(ptr) {}

    explicit operator bool() const { return ptr == nullptr; }
};

int main() {
    Latitude lat1(1.0);
    double a = static_cast<double>(lat1);
    {
        // explicit keyword

        Latitude lat1 = 1.0;            // CE
        Latitude lat2 = Latitude(1.0);  // OK
        Latitude lat3(1.0);             // Best

        std::cout << lat2.val << '\n';
    }

    {
        int* p = nullptr;
        if (p) {  // Poor, use p != nullptr
            std::cout << "yes\n";
        }
    }

    {
        // contextual conversion

        PointerWrapper w(nullptr);
        bool val = w;          // CE, implicit conversion
        bool e_val = bool(w);  // OK, explicit conversion
        if (w) {               // OK, contextual conversion
            std::cout << *w.ptr << '\n';
        } else {
            std::cout << "nullptr\n";
        }

        for (;w;) {
        }

        while (w) {}
    }
}
