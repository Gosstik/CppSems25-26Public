#include <memory>

// operators do not obey to access modifiers in comparizon with functions

class A {
  public:
    std::unique_ptr<A> CreateNextBad() {
        return std::make_unique<A>(val);  // CE
    }

    std::unique_ptr<A> CreateNextRight() {
        return std::unique_ptr<A>(new A(val));  // OK
    }

  private:
    A(int val) : val(val) {}

    int val;
};

int main() {}
