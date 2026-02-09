#include <iostream>

struct Granny {
  // friend int main();
  void Foo() {}
  int x;
};

struct Mom : private Granny {
  // friend int main();
  int x;
};

struct Son : Mom {
  int x;
};

int main() {
  Son s{};
  std::cout << s.Granny::x << '\n';  //* OK
}
