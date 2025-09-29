#include <vector>

int main() {
  std::vector<int> polynom(10, 2);
  std::vector<int> odd;
  std::vector<int> even;
  for (size_t i = 0; i < polynom.size(); i++) {
    (i % 2 == 0 ? even.push_back(polynom[i]) : odd.push_back(polynom[i]));
  }
}
