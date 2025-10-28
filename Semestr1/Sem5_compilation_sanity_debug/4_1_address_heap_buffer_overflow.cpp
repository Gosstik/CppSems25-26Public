#include <iostream>
#include <vector>

// Address Sanitizer == ASAN

// clang++ -std=c++20 -fsanitize=address -g main.cpp

int main() {
  std::vector<int> vec(10, 1);
  std::cout << vec[10] << '\n';
}
