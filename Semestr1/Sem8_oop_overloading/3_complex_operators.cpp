#include <iostream>

// operator+=() (aka "compound assignment")
// operator+() --- not a method or friend, simple implementation with +=
// Copy elision, RVO and NRVO using operator+()
// a + b = 5 // return const or mark operator=() with ref qualifier
// NO return a += b // nrvo (see copy_elision.cpp)
// ++a and a++
// comparisons, (a > b) == (b < a)
// spaceship
// operator==() = default (since C++20)

#include <compare>
#include <iostream>

struct Complex {
    double re = 0.0;
    double im = 0.0;

    // ORDER IS SUFFICIENT !!! Try with -Wall
    Complex(double re = 0, double im = 0) : re(re), im(im) {
        std::cout << "Ctor\n";
    }

    Complex(const Complex& other) : re(other.re), im(other.im) {
        std::cout << "Copy ctor\n";
    }

    Complex& operator=(const Complex& other) & {
        if (this == &other) {
            return *this;
        }
        re = other.re;
        im = other.im;
        std::cout << "operator=()\n";
        return *this;
    }

    //  // Better to be outside of the class
    //  Complex operator+(const Complex& other) const {
    //    return Complex(re + other.re, im + other.im);
    //  }

    //  // Poor implementation
    //  Complex& operator+=(const Complex& other) {
    //    *this = *this + other;
    //    return *this;
    //  }

    Complex& operator+=(const Complex& other) {
        re += other.re;
        im += other.im;
        return *this;
    }

    Complex& operator++() & {
        ++re;
        return *this;
    }

    Complex operator++(int) {
        Complex copy = *this;
        ++*this;
        return copy;
    }

    ~Complex() { std::cout << "Dtor\n"; }

    ///////////////////////////

    // Three-way comparison (since C++20)
    // auto == strong, week, partial ordering
    auto operator<=>(const Complex& other) const = default;

    std::weak_ordering operator<=>(const char* other) const {
        return std::weak_ordering::equivalent;
    }
};

////////////////////////////////

// operator+

// // Bad implementation of operator+ 1
// Complex operator+(Complex lhs, const Complex& rhs) {
//   return lhs += rhs;
// }

// // Bad implementation of operator+ 2
// Complex operator+(const Complex& lhs, const Complex& rhs) {
//   Complex res = lhs;
//   return res += rhs;
// }

// operator+ specific for Complex
Complex operator+(const Complex& lhs, const Complex& rhs) {
    return Complex(lhs.re + rhs.re, lhs.im + rhs.im);
}

// // General way to make operator+
// Complex operator+(const Complex& lhs, const Complex& rhs) {
//   Complex res = lhs;
//   res += rhs;
//   return res; // NRVO - named return value optimization
// }

////////////////////////////////

// Comparisons

// == !=
// < > <= >=

bool operator==(const Complex& lhs, const Complex& rhs) {
    return lhs.re == rhs.re && lhs.im == rhs.im;
}

bool operator<(const Complex& lhs, const Complex& rhs) {
    return lhs.re < rhs.re || (lhs.re == rhs.re && lhs.im < rhs.im);
}

bool operator<=(const Complex& lhs, const Complex& rhs) { return !(rhs < lhs); }

bool operator>(const Complex& lhs, const Complex& rhs) { return rhs < lhs; }

int main() {
    Complex c(1.0);

    //   {
    //     Complex c(1.0);
    //     c + 3.14;  // c.operator+(3.14);
    //     3.14 + c;  // CE if overloading inside class
    //     1 + c = 1; // CE
    //     c = 1; // OK
    //   }
}
