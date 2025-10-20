#include <iostream>

int One() {
  std::cout << 1;
  return 1;
}

int Two() {
  std::cout << 2;
  return 2;
}

int Three() {
  std::cout << 3;
  return 3;
}

int All(int a, int b, int c) {
  return a * One() + b * c + Two() * Three();
}

int main() {
  std::cout << All(One(), Two(), Three()) << '\n';
}
