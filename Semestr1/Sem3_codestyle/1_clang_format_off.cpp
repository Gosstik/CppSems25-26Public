#include <iostream>

int Formatted(int x, int y) {
    std::cout << "Accepted " << x << "and " << y << '\n';
    int sum = x + y;
    std::cout << "Sum:" << sum << std::endl;
    return x * x + y * y;
}

// clang-format off

int Unformatted(
    int x,
    int y
) {
        std::cout << "Accepted "
      << x << "and "                << y << '\n'
    ;
    int
sum = x + y    ;



    std::cout<<"Sum:"<<sum<<std::endl;return x*x+y*y;
}

// clang-format on

int main() {
    Formatted(1, 2);
    Unformatted(1, 2);
}
