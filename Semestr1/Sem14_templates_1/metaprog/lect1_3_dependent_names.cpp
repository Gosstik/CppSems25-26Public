template <class T>
struct C {
  void f() {
    T t;
    t.foo();
    foo(t);
    foo<T>();
    T::C c;
  }
};

////////////////////

// Will compile?

// cppreference: dependent name

template <typename T>
struct A {
  void g() {

  }
};

template <class T>
struct C: A<T> {
  void f() {
    g();
    //* this->g();
  }
};

////////////////////

// Will compile?

//* Remove comments

// Rule:
// Specialization always include:
// 1. members
// 2. usings
// Only when used
// 1. methods
// 2. static variables
// 3. subtypes

template <typename C>
struct Smth {
  C value;

  int GetTMember() {
    return value.member;
  }
};

Smth<int> smth{};

