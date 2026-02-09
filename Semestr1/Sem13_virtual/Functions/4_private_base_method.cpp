#include <iostream>

// Explanation:
// Privacy: compile time phenomenon
// Virtual: runtime phenomenon

// ??? static virtual function

struct Granny {
    virtual void Foo() const { std::cout << 1 << '\n'; }
};

struct Mom : Granny {
  private:
    void Foo() const override { std::cout << 2 << '\n'; }
};

struct Son : Mom {
    void Foo() const final { std::cout << 3 << '\n'; }
};

int main() {
    Mom m;
    Granny& g = m;
    g.Foo();
}
