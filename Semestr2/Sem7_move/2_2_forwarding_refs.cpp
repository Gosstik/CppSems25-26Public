#include <iostream>
#include <string>
#include <type_traits>
#include <utility>

// Forwarding (Universal) references

// Reference is universal in case it satisfies all conditions:
// 1) T is template argument of current function
// 2) T&& is accepted
// 3) It is argument of a function

// Is code correct? How to improve it?

// void Foo(const int&) {

// }

// void Foo(int&&) {

// }

template <typename T>
void Foo(T&& rv) {
    static_assert(std::is_same_v<T, int> || std::is_same_v<T, int&>);
    // static_assert(std::is_same_v<T, int>);
    // static_assert(std::is_same_v<T, int&>);
}

struct S {
    S(std::string& ls, std::string&& rs, const int i) : ls(ls), rs(rs), i(i) {}

    std::string& ls;
    std::string rs;
    int i;
};

template <typename... Args>
S GetS(Args&&... args) {
    std::cout << "Creating S\n";
    return {std::forward<Args>(args)...};
    // return {args...};
}

int main() {
    std::string ls = "abc";
    S s = GetS(ls, "def", 5);

    int a = 1;
    Foo(a);             // T = int&
    Foo(1);             // T = int
    Foo(std::move(a));  // T = int
}
