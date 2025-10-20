#include <iostream>
#include <vector>

void Foo(int x) {
    std::cout << x << '\n';
}

void Foo(std::vector<int>& v) {
    for (size_t i = 0; i < v.size(); ++i) {
        std::cout << v[i] << ' ';
    }
    std::cout << '\n';
}

int main() {
    int a;
    std::vector<int> v{1, 3, 5};

    Foo(a); // OK
    Foo(v); // OK
}
