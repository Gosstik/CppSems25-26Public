#include <iostream>

void Print() { std::cout << '\n'; }

template <typename Head, typename... Args>
void Print(Head head, Args... args) {
    std::cout << head << ' ';
    Print(args...);
}

template <typename... Args>
void PrintCount(Args... args) {
    std::cout << sizeof...(args) << '\n';
}

// // CE, not a parameter pack
// void CountInts(int... args) {
//   std::cout << sizeof...(args) << '\n';
// }

int main() {
    Print(1, 2.9, 'c', "abcd");
    std::cout << '\n';
    PrintCount(1, 2.9, 'c', "abcd");
}
