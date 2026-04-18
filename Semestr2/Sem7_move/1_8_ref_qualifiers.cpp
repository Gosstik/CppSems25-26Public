#include <iostream>
#include <string>

struct S {
    std::string s = "abc";

    std::string Get() const& { return s; }

    std::string Get() && { return std::move(s); }
};

S Foo() { return {"Foo"}; }

int main() {
    std::cout << S("abc").Get() << '\n';

    std::cout << Foo().Get() << '\n';
    std::cout << std::move(Foo().s) << '\n';

    S s("def");
    std::cout << std::move(s).Get() << ' ' << s.s.size() << '\n';
}
