#include <iostream>

class C {};

class S {
  public:
    int x = 0;
    int y = 1;
    int z = 2;

    void Foo() { x = 10; }

  private:
};

struct Outer {
    // private:
    using Size = int;

    struct Inner {
        using InnerSize = Size;
        int b;

        void Foo(Outer o) { o.a = 10; }
    };

  private:
    int a;
};

int main() {
    {
        S s;
        s.Foo();
        s.x = 10;
        s.y = 1;

        std::cout << sizeof(Outer) << '\n';  // ???
    }

    {
        // from C
        S s = {
            .y = 4,
            .z = 5,
        };

        std::cout << s.x << s.y << s.z << '\n';
    }
}
