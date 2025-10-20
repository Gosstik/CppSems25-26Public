#include <iostream>

int main(int argc, char* argv[]) {
  std::cout << "Total accepted: " << argc << '\n';

  std::cout << "Result: ";
  for (int i = 1; i < argc; ++i) {
    if (i == 1) {
      std::cout << argv[i];
      continue;
    }
    std::cout << " " << argv[i];
  }
  std::cout << '\n';

  return 0;
}
