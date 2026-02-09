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
    void Bar() {}
};

template <class T>
struct S : A<T> {
    void Foo() {
        Bar();
        // this->Bar();
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

template <typename T>
struct Smth {
    T value;

    int GetTMember() { return value.member; }
};

int main() { Smth<int> smth{}; }
