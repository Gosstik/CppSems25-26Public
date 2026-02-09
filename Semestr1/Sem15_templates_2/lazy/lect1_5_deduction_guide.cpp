// vector(Iter, Iter)
// example: vector(";", ",")
// auto in template

struct C {
    void Foo() {}
};

// pointer to member function
template <typename T, class V, int I, void C::* Foo()>
struct S {};

//////////////////

template <auto V>
struct S2 {};

S2<123> s;  // decltype(V) = int

/////////////////

template <typename T, T V>
struct S3 {};

S3<int, 123> s3;

/////////////////

// Template values must be POD types (Plain Old Data), such as A

struct A {
    int a;
    long long b;
};

template <A V>
struct S4 {};

S4<A{1, 2}> s4;
