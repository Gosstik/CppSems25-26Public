// vector(Iter, Iter)
// example: vector(";", ",")
// auto in template

struct C {};

// pointer to member function
template <typename T, class V, int I, void C::*F()>
struct S{};

//////////////////

template <auto V>
struct S2 {};

S2<123> s; // decltype(V) = int

/////////////////

template <typename T, T V>
struct S3 {};

S3<int, 123> s3;


/////////////////

struct A {
  int a;
  long long b;
};

template <A V>
struct S4 {};

S4<A{1, 2}> s4;

/////////////////

template <typename T>
struct A5 {};

template <template<class> class T>
struct S5 {
  T<int> a;
};

S5<A5> s5;
