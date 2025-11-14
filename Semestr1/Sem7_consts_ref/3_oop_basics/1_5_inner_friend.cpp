#include <iostream>

struct Before {};

class C {
  private:
    int x_{5};

  public:
    void Foo(int y) { std::cout << x_ + y << '\n'; }

    friend void Bar(C, int);

    friend void Baz(C, int) { std::cout << "Hi!\n"; }

    // You can call that function nowhere...
    friend void Bazz(int) { std::cout << "Hi!\n"; }

    friend Before;         // OK
    friend struct Before;  // OK
    friend After;          // CE !!!
    friend struct After;   // OK
};

struct After {};

void Bar(C c, int y) { std::cout << c.x_ + y + 1; }

int main() {
    C c;

    {
        c.Foo(1);   // OK
        Bar(c, 1);  // OK
    }

    {
        // C::Baz(c, 1); // CE !!!
        Baz(c, 1);  // OK
    }

    {
        Bazz(1);     // CE
        C::Bazz(1);  // CE
    }
}
