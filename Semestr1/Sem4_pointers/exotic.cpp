#include <ios>
#include <iostream>

int main() {
  {
    char ss[] = "abc"; // O(len)
    const char* s1 = "abc"; // O(1)
    const char* s2 = "abc";
    std::cout << (void*)s1 << ' ' << (void*)s2 << '\n';
    std::cout << "s1 = s2: " << std::boolalpha << (s1 == s2) << '\n'; // unspecified
  }
}