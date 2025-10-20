#include <iostream>

// Tail recursion optimization

// Try with godbolt
// Compile: g++ -std=c++20 -O2 factorial_tail_recursion.cpp

// More: https://habr.com/ru/companies/pvs-studio/articles/261027/

int global_counter = 1;

int Factorial(int n) {
  if (n < 2) {
    return 1;
  }

  std::cout << global_counter << '\n';
  global_counter++;

  return n * Factorial(n - 1);
}

int FactorialInfty(int n) {
  if (n < 2) {
    return 1;
  }

  std::cout << global_counter << '\n';
  global_counter++;

  return n * FactorialInfty(n);
}

int main() {
  std::cout << Factorial(5) << std::endl;
  // std::cout << FactorialInfty(5) << std::endl;
}
