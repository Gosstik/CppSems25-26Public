#include <iostream>
#include <cstddef>

int main() {
  char ch{};
  char res[10] = {};
  size_t res_size = 0;
  while (std::cin.get(ch)) {
    if (ch != '\n') {
      res[res_size] = ch;
      ++res_size;
    } else {
      res[res_size] = '\0';
      std::cout << "res = " << res << '\n';
      res_size = 0;
    }
//    std::cout << "char = " << '"' << ch << '"' << '\n';
  }
}
