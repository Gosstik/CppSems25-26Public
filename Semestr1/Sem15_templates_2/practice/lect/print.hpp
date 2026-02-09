#pragma once

#include <iostream>

void Print() { std::cout << '\n'; }

template <typename Head, typename... Args>
void Print(Head head, Args... args) {
    std::cout << head << ' ';
    Print(args...);
}

template <typename... Args>
void FoldPrint(const Args&... args) {
    ((std::cout << args << ' '), ...);
    std::cout << '\n';
}

void TestPrint() {
    // Print(1, 2.9, 'c', "abcd");
    FoldPrint(1, 2.9, 'c', "abcd");
    FoldPrint();
}
