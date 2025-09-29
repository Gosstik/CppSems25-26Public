#include <iostream>

// Keep in mind array to pointer conversion.

void Foo(int**) {
  std::cout << 1;
}

void Foo(int (*)[5]) {
  std::cout << 2;
}

void Foo(int[5][5]) {
  std::cout << 4;
}

int main() {
  int a[5];
  Foo(&a);

  int* b = a;
  Foo(&b);
}
