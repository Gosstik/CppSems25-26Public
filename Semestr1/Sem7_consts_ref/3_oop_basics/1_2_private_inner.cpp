#include <iostream>

class C {
  private:
    class Inner {
      public:
        int x = 1;

      private:
        int y_ = 2;
    };

  public:
    Inner GetInner() { return Inner(); }
};

int main() {
    C c;
    std::cout << c.GetInner().x;  // CE or 1?

    // Local struct
    struct Local {
        int val = 10;
    };
}
