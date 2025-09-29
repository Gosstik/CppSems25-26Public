#include <iostream>

int* Foo() {
  int* p = new int;
  *p = 5;
  std::cout << *p << '\n';
  return p;
}

int main() {
    // !!! We are responsible for freeing memory
    int* foo = Foo();
    *foo = 10;
    std::cout << *foo << '\n';
    delete foo;
}
