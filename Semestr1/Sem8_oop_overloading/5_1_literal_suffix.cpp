#include <iostream>
#include <string>

// Integer literals (existing)
// https://en.cppreference.com/w/cpp/language/integer_literal

// User-defined literals
// https://en.cppreference.com/w/cpp/language/user_literal

//// decimal-literal ud-suffix
// ( unsigned long long int ) -> operator ""X(nULL)
// ( long double )
// ( const char* ) -> operator""X("n")

//// Last version is a fallbacks for integer and floating-point
//// user-defined literal

//// character-literal ud-suffix
// ( char )
// ( wchar_t )
// ( char8_t )
// ( char16_t )
// ( char32_t )

//// string-literal ud-suffix
// ( const char*, std::size_t )
// ( const wchar_t*, std::size_t )
// ( const char8_t*, std::size_t )
// ( const char16_t*, std::size_t )
// ( const char32_t*, std::size_t )

////  Literal operators can be overloaded

struct Latitude {
    double val;
    explicit Latitude(double val) : val(val) {}

    explicit operator double() const { return val; }
};

// -1234_mysuf == operator-(1234_mysuf)

Latitude operator""_lat(long double d) {
    return Latitude(d);  // NOLINT
}

// tests

void Foo(Latitude lat) {
    std::cout << "Insode Foo: ";
    std::cout << lat.val << '\n';
}

int main() {
    {
        Latitude lat1 = 1.0_lat;
        std::cout << lat1.val << '\n';

        Foo(3.0_lat);
    }

    {
        // using namespace std::string_literals;
        using std::string_literals::operator""s;

        auto s = "abc"s;  // std::string
    }
}
