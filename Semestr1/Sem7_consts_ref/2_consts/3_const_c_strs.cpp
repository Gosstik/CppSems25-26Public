#include <iostream>

using FooArray10Type = const char[10];

void Foo(FooArray10Type& arr) {
    std::cout << "Array 10 version" << '\n';
    // std::cout << "sizeof(arr) = " << sizeof(arr) << '\n'; // ???
}

void Foo(const char (&arr)[11]) { std::cout << "Array 11 version" << '\n'; }

void Foo(const char*& arr) { std::cout << "Pointer version" << '\n'; }

int main() {
    {
        // const and pointers
        const char* s1 = "abc";
        s1[1] = 'b';  // ???
        s1 = "cde";   // ???

        char const* s2 = "abc";
        s2[1] = 'b';  // ???
        s2 = "cde";   // ???

        char* const s3 = "abc";
        s3[1] = 'b';  // ???
        s3 = "cde";   // ???

        const char* const s4 = "abc";
        s4[1] = 'b';  // ???
        s4 = "cde";   // ???
    }

    {
        const char* ptr = "1234567890";
        Foo(ptr);
        Foo("123456789");
    }
}
