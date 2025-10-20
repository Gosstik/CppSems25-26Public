#include <iostream>

void Bar(int**) {  // 1
  std::cout << 1 << '\n';
}

void Bar(int (*)[3]) {  // 2
  std::cout << 2 << '\n';
}

// void Bar(int[3][3]) {  // 3
//   std::cout << 3 << '\n';
// }

// void Bar(int[][3]) {  // 4
//   std::cout << 4 << '\n';
// }

// void Bar(int[3][]) {  // 5
//   std::cout << 5 << '\n';
// }

int main() {
  // 2 == 3 == 4
  // 5 - CE

  int a[3][3]{};
  Bar(a);  // 2

  int(*b2)[3] = a;
  Bar(b2); // 2

  int x[3];
  Bar(&x); // 2

  int* px = x;
  Bar(&px); // 1
}
