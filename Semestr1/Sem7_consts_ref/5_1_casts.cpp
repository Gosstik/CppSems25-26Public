#include <iostream>

// https://en.cppreference.com/w/cpp/language/static_cast.html
// https://en.cppreference.com/w/cpp/language/const_cast.html
// https://en.cppreference.com/w/cpp/language/reinterpret_cast.html
// https://en.cppreference.com/w/cpp/language/explicit_cast.html

// Numeric cast:

int main() {
    {
        int i = 0;
        double d = i;                        // OK
        double sd = static_cast<double>(i);  // OK
    }

    {
        double d = 0.0;
        int i = d;  // Narrowing conversion from 'double' to 'int'
        int si = static_cast<int>(d);  // OK
    }

    {
        // reinterpret_cast
        long long x = 1729;
        std::cout << reinterpret_cast<double&>(x) << '\n';  // UB
    }

    {
        // TODO: const_cast
    }

    {
        // TODO: C-style cast (explicit cast)
    }

    {
        // Brace/List Initialization
        // https://en.cppreference.com/w/cpp/language/list_initialization.html
        int64_t val = 1;
        int a = int(val); // OK, may overflow and cause UB
        int b = int{val}; // CE, narrowing conversion
    }
}
