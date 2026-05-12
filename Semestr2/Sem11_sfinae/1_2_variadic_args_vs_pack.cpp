#include <vector>

// https://en.cppreference.com/w/cpp/language/variadic_arguments
// https://en.cppreference.com/w/cpp/language/pack

// TODO: link to POD type definition

//// Problem with POD types

int Foo(...) {  // variadic arguments
    return 1;
}

template <typename... Args>  // template parameter pack
int Bar(Args...) {           // function parameter pack
    return 2;
}

struct Base {
    int b;
};

struct NotPOD : private Base {
    // std::vector<int> v;
  private:
    int a;
};

void Test1() {
    decltype(Foo(NotPOD())) foo = 1;  // OK
    Foo(NotPOD());                    // CE (or warning)

    decltype(Bar(NotPOD())) bar = 2;  // OK
    Bar(NotPOD());                    // OK
}

////////////////////////////////////////////////////////////////////////////////

//// Ambiguous call

void Baz1() {}
void Baz1(...) {}

void Baz2() {}

template <typename...>
void Baz2(...) {}

void Test2() {
    // Baz1();  // CE: ambiguous call
    Baz2();  // OK
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    Test1();
    Test2();
}
