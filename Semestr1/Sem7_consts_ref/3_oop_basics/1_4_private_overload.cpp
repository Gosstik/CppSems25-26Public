#include <iostream>

struct C {
  private:
    void Foo(int) { std::cout << 1; }

  public:
    void Foo(float) { std::cout << 2; }
};

int main() {
    //* Explanation: The overload version is selected before the privacy check.

    C c;
    // c.Foo(0);     // CE or 1?
    c.Foo(3.14);  // CE or 2?
}
