#include <functional>
#include <iostream>
#include <vector>

int main() {
  {
    // Basics

    int x = 0;
    std::reference_wrapper<int> rx = x;
    // rx = 1; // CE
    rx.get() = 1;
  }

  {
    // vector with reference wrapper

    std::vector<std::reference_wrapper<int>> a;
    int x = 0;
    int y = 1;
    a.push_back(x);
    a.push_back(std::ref(y));

    x = 1;
    y = 2;

    std::cout << a[0] << a[1] << '\n';

    // a[0] = 0;  // CE
    a[0].get() = 0;

    std::cout << a[0] << a[1] << '\n';
  }
}
