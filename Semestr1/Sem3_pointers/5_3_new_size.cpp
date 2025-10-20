#include <iostream>

int main() {
  {
    // Pointers may be reused after delete
    int* rp = new int(10);
    delete rp;
    rp = new int(20);
    delete rp;
  }

  {
    // UB: size of dynamic array
    int* p1 = new int[100];
    int* p2 = new int[1000];
    int* p3 = new int[4000];
    std::cout << p1[-2] << ' ' << p2[-2] << ' ' << p3[-2] << '\n';
  }
}
