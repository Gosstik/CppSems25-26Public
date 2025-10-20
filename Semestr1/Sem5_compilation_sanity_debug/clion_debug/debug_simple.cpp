#include <iostream>

int Foo(int a, int b) {
  // add watch: a + b
  a += 2;
  b += 3;

  int res = a + b;
  res *= 2;
  return res;
}

int main() {
  int* abc = nullptr;
  int a = 1;
  int b = 2;
  int c = Foo(a, b);
  std::cout << c << std::endl;
}
