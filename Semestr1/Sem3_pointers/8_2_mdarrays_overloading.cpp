#include <iostream>

// Keep in mind array to pointer conversion.

// 1
void Foo(int**) {
  std::cout << 1;
}

// 2
void Foo(int (*a)[5]) {
  std::cout << 2;
}

// 3
void Foo(int[5][5]) {
  std::cout << 3;
}

int main() {
  int a[5];
  Foo(&a); // ???

  int* b = a;
  Foo(&b); // ???
}
