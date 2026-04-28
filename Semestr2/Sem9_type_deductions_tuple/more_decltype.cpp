#include <iostream>

template <typename T>
struct IsRef : std::false_type {};

template <typename T>
struct IsRef<T&> : std::true_type {};

int main() {
  int x = 0;
  int& y = x;
  int&& z = std::move(x);

  std::cout << IsRef<decltype((x))>::value << '\n';
  // std::cout << IsRef<decltype(y)>::value << '\n';
  // std::cout << IsRef<decltype((z + 1))>::value << '\n';
}
