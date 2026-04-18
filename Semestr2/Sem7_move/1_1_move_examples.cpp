#include <iostream>
#include <string>

// If object is rvalue --- compiler calls move ctor
// If object is lvalue --- compiler calls copy ctor
// std::move(val) --- force compiler treat val as rvalue. It returns T&&

// !!! bit field does not have address, but it is lvalue
// !!! C array is lvalue, but it cannot stand to the left of =

// For primitive types move is useless !!!

// What if call std::move() without acquiring value ???

int main() {
    int x;
    int& y = (x = (1 + x));
    int&& z = (1 + x);

    z += 10;
    y = 20;

    int& y2 = (1 + x);
    int&& z2 = (x = (1 + x));

    // const int& x3 = 1;
    // T v = T(T(T()));

    {
        int x = 1;     // ???
        int&& y = 2;   // ???
        int&& z1 = y;  // ???

        int&& z2 = std::move(y);           // ???
        int&& z3 = static_cast<int&&>(y);  // ???
        int z4 = static_cast<int&&>(y);    // ???
        int&& z5 = (int&&)y;               // ???

        z2 = 0;                  // ???
        std::cout << y << '\n';  // ???
    }

    {
        int&& x = 2;                  // ???
        int& y = x;                   // ???
        int&& z = std::move(x);       // ???
        y = 3;                        // ???
        ++y;                          // ???
        std::cout << x << y << '\n';  // ???
    }

    {
        int&& a = 3;                   // ???
        const int&& b = std::move(a);  // ???
        const int& c = b;              // ???
        const int&& d = 2;             // ???
    }

    {
        int x = 0;
        int& y1 = (true) ? ++x : x++;   // ???
        int&& y2 = (true) ? ++x : x++;  // ???

        // (a, b)
    }
}
