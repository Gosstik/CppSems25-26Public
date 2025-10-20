#include <iostream>

// Try -O flags on godbolt

int main() {
  int ind = 0;
  for (int i = 0; i < 10; ++i) {
    ++ind;
  }
  int j = 1;
  std::cout << j << std::endl;
}
