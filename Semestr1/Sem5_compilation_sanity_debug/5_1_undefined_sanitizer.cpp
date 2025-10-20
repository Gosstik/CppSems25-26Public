// Undefined Sanitizer == UBSAN

#include <iostream>
#include <climits>

int main() {
    // Example 1: Integer overflow
    int max_int = INT_MAX;
    int result = max_int + 1;  // This causes signed integer overflow (UB)

    std::cout << "max_int: " << max_int << std::endl;
    std::cout << "result: " << result << std::endl;

    // Example 2: Division by zero
    int a = 10;
    int b = 0;
    int division = a / b;  // Division by zero is UB

    std::cout << "10 / 0 = " << division << std::endl;
}
