

template <typename T, typename U>
struct A {
    T t;
    U u;
};

//// deduction guide for c++17
template <typename T, typename U>
A(T, U) -> A<T, U>;

////////////////////////////////////////////////////////////////////////////////

template <typename T, typename U>
struct B : T, U {};

//// deduction guide for c++17
template <typename T, typename U>
B(T, U) -> B<T, U>;

////////////////////////////////////////////////////////////////////////////////

template <typename... Args>
struct C : Args... {};

//// deduction guide for c++17
template <typename... Args>
C(Args...) -> C<Args...>;

////////////////////////////////////////////////////////////////////////////////

struct Tag1 {};
struct Tag2 {};
struct Tag3 {};

int main() {
    // all are OK, since c++20 without deduction guide
    A{1, 2.0};
    B{Tag1{}, Tag2{}};
    C{Tag1{}, Tag2{}, Tag3{}};
}
