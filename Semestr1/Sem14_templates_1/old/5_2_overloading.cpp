#include <iostream>
#include <cstdint>

template <typename U, typename T>
U Foo(T x) {
  std::cout << 1;
  return x;
}

void Foo(int32_t x) {
  std::cout << x;
}

int main() {
  int64_t x = 0;
  int g1 = Foo<int32_t>(x); // OK
  // int g2 = Foo(x); // CE
}
