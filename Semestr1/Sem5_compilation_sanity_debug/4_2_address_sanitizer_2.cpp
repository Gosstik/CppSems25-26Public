#include <iostream>
#include <vector>

void Foo() {
  std::vector<int> vec(10, 1);
  int* vptr = &vec[1];
  vec.push_back(1);
  std::cout << *vptr << '\n';
}

int main() {
  Foo();
}
