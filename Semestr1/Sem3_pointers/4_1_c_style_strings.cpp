#include <iostream>

int main() {
    // Actual type of "Hello, world!" ???

    char s1[] = "Hello, world!";
    // s1[2] = 'c';
    const char s2[] = "Hello, world!";
    // s2[2] = 'c'; // CE
    const char* s3 = "Hello, world!";
    char* s4 = "Hello, world!"; // UB since C++11

    // s4[1] = 'c';
    // std::cout << s4 << '\n';

    std::cout << s2 << '\n';

    char str_arr1[] = "abcde"; // copy of "abcde" to str_arr
    char str_arr2[] = {'a', 'b', 'c', 'd', 'e'};
    std::cout << sizeof(str_arr1) << ' ' << sizeof(str_arr2) << '\n'; // ???

    // Null terminator (C style strings == Null-terminated strings)
    char zero_str[] = "abc\0def";
    std::cout << zero_str << ' ' << sizeof(zero_str) << '\n'; // ???
}
