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
        std::cout << m.y_ << m.x << g.x;
    }
    // friend class Son;

  private:
    int y_ = 1;
};

class Son : private Mom {
    void Foo(Mom m) {
        ::Granny& g = m;  //* CE, but OK with protected inheritance

        std::cout << Mom::x;  //* CE with private inheritance, OK with protected
                              //inheritance
        std::cout << m.x;     //* CE with both inheritance, OK if Son is friend
        std::cout << g.x;     //* always OK
    }
};

int main() {}
