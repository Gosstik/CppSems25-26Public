#include <iostream>

// Last sem in Semestr2

// strict aliasing
// ! compile without sanitizers

//// Solutions:
// -fno-strict-aliasing
// make "volatile int* i" in Foo()

// !!! replacing float* to char* removes UB
// (char* and std::byte are exceptions in standard)
int Foo(float *f, int *i) {
  *i = 1;
  *f = 0;

  return *i;
}

int main() {
  int x = 0;

  std::cout << x << "\n";  // Expect 0
  x = Foo(reinterpret_cast<float *>(&x), &x);
  std::cout << x << "\n";  // Expect 0 ?
}
