#include <cstring>

// See types of initialization on cppreference:
// - List initialization
// - Aggregate initialization
// - Direct initialization
// - Value initialization
// - Copy initialization
// ...

// https://www.reddit.com/r/ProgrammerHumor/comments/8nn4fw/forrest_gump_learns_c/

// !!! Order in member initializer list is NOT important.
// !!! Only sequence of fields declaration matters.

class Complex {
  public:
    // ??? How to simplify
    Complex() {}
    Complex(double re) : re_(re) {}
    Complex(double re, double im) : re_(re), im_(im) {}

    //  Complex(double real) {
    //    re = real;
    //    // this->re = re;
    //  }

  private:
    double re_ = 0.0;
    double im_ = 0.0;
};

int main() {
    // Possible construction (do not try to remember that)
    Complex c(5.0);      // Direct initialization
    Complex c2 = 5.0;    // Copy initialization
    Complex c3{5.0};     // Uniform initialization
    Complex c4 = {8.0};  // Aggregate initialization
}
