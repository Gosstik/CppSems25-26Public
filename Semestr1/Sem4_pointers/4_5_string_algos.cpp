#include <cstring>

#include <algorithm>
#include <iostream>
#include <vector>

bool LexicalStringsCmp(const char* lhs, const char* rhs) {
  return strcmp(lhs, rhs) < 0;
}

void StrlenExample() {
    // strlen

    const char* str = "Hello, world!\n";
    size_t len = strlen(str);
    for (size_t i = 0; i < len; ++i) {
      std::cout << str[i];
    }
    std::cout << '\n';

    // Difference sizeof() and strlen(): O(1) and O(len)
    // sizeof() --- compile time concept, it is REPLACED WITH VALUES in asm
    // strlen() --- runtime concept, it is evaluated in cycle
    const char* s = "abc\0def";
    std::cout << strlen(s) << ' ' << sizeof(s) << '\n';
}

void StrcmpExample() {
    // strcmp
    // https://en.cppreference.com/w/cpp/string/byte/strcmp

    // lexicographical comparison
    std::vector<const char*> strs{"aab", "bc", "abc", "a", "ca", "bb", "bbc"};
    std::sort(strs.begin(), strs.end(), LexicalStringsCmp);

    for (const char* str : strs) {
      std::cout << str << '\n';
    }
}

void ConversionsExample() {
    // atoi --- alphabetical to int
    // https://en.cppreference.com/w/cpp/string/byte/atoi

    // atof           --- alphabetical to float
    // strtol         --- more convenient and allows to parse different base
    // std::to_string --- transform <integer> to std::string

    char str_int[] = "   123+456";
    int a = atoi(str_int);
    std::cout << "a = " << a << '\n'; // 123

    char str_float[] = "243.4e-2"; // == 2.434
    float f = atof(str_float);
    std::cout << "f = " << f << '\n';

    char** p = nullptr;
    int64_t res = strtol(str_int, p, 10);
    std::cout << str_int << ' ' << *p; // out: 123 +456

    std::cout << std::to_string(res) + std::to_string(res) << '\n';
}

void StrcpyExample() {
    // strcpy

    const char* src = "Some short string";
    // ...
    char buf[100]{};
    strcpy(buf, src);
    size_t len = strlen(buf);
    for (size_t i = 0; i < len; ++i) {
      std::cout << buf[i];
    }
    std::cout << '\n';
}

void MemcpyExample() {
    // memcpy, memmove

    int a1[5] = {1, 2, 3};
    int a2[3] = {5, 6};
    size_t a1_len = sizeof(a1) / sizeof(int);
    size_t a2_len = sizeof(a2) / sizeof(int);

    memcpy(a1, a2, std::min(sizeof(a1), sizeof(a2))); // OK
    // memcpy(a1, a1 + 1, (a1_len - 1) * sizeof(int)); // UB
    // memmove(a1, a1 + 1, (a1_len - 1) * sizeof(int)); // OK

    // std::copy(a1, a1 + a1_len - 1, a1 + 1); // UB
    // std::copy_backward(a1, a1 + a1_len - 1, a1 + 1); // OK

    for (size_t i = 0; i < a1_len; ++i) {
      std::cout << a1[i] << ' ';
    }

    char c[] = "Hello"; // char[]

    std::cout << '\n';

    for (size_t i = 0; i < a2_len; ++i) {
      std::cout << a2[i] << ' ';
    }

    // memcpy vs strcpy: "abc\0cde"
}

void CopyExample() {
    // std::copy and std::copy_backward
    std::vector<size_t> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    auto b = vec.begin();
    auto e = vec.end();

    // can't use memcpy and memmove

    std::copy(b, b + 5, b + 5); // OK
    // std::copy(b, b + 5, b + 1); // UB
    // std::copy_backward(b, b + 5, b + 6); // OK, same as above
    // std::copy_backward(b + 5, b + 10, b + 6); // UB

    for (auto elem: vec) {
      std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    StrlenExample();
    StrcmpExample();
    ConversionsExample();
    StrcpyExample();
    MemcpyExample();
    CopyExample();
}
