#include <iostream>

// 1) CE or OK? Why?
// 2) Uncomment `friend class Son;`
// 3) Change inheritance of Granny from private to protected. What happens?

class Granny {
    friend class Mom;

  public:
    int x = 0;
};

class Mom : private Granny {
    void Foo(Mom m) {  // NOLINT
        Granny& g = m;
        std::cout << m.y_ << m.x << g.x;  // ???
    }
    // friend class Son;

    protected:
    int c = 10;

  private:
    int y_ = 1;
};

class Son : private Mom {
    void Foo(Mom m) {
        ::Granny& g = m;      // ???
        std::cout << Mom::x;  // ???
        std::cout << m.x;     // ???
        std::cout << g.x;     // ???

        c += 10; // OK
        m.c += 10; // CE
    }
};

int main() {}
