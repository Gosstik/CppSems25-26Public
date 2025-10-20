#include <cstdint>
#include <iostream>

void Foo(int) {}
void Foo(double) {}
void Foo(bool);

void Bar(long long) {}

int main() {
    std::cout << (void*)Foo << '\n';  // CE

    void (*fooi)(int) = Foo;   // OK
    void (*foob)(bool) = Foo;  // OK

    void (*barll)(long) = Bar;              // CE
    void (*barcll)(const long long) = Bar;  // OK
}
