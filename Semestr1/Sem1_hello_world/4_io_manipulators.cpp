#include <iomanip>
#include <iostream>

int main() {
    // Partial replace for printf - Input/output manipulators from <iomanip>
    // More: https://en.cppreference.com/w/cpp/io/manip

    std::cout << "Booleans:\n";
    std::cout << "1: " << std::boolalpha << 1 << '\n'
              << "0: " << std::boolalpha << 0 << '\n';

    ////////////////////////////////////////////////////////////////////////////
    std::cout << '\n';

    std::cout << "Other base:\n";
    std::cout << "The number 42 in octal:   " << std::oct << 42 << '\n'
              << "The number 42 in decimal: " << std::dec << 42 << '\n'
              << "The number 42 in hex:     " << std::hex << 42 << '\n';

    std::cout << '\n';

    ////////////////////////////////////////////////////////////////////////////
    std::cout << "Floating point:\n";
    long double pi = 3.141592653589793;
    // long double pi = std::numbers::pi_v<long double>;

    auto default_precision = std::cout.precision();
    int max_precision = 15;
    // int max_precision = std::numeric_limits<long double>::digits10 + 1;

    std::cout << "default precision: " << default_precision << '\n'
              << "maximum precision: " << max_precision
              << "\n\n"
                 "precision: pi:\n";

    for (int p = 0; p <= max_precision; ++p) {
        std::cout << std::setw(2) << p << ":  " << std::setprecision(p) << pi
                  << '\n';
    }

    std::cout << std::setprecision(default_precision);  // restore defaults
}
