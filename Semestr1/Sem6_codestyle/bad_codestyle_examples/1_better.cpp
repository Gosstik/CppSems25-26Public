#include <cstdint>
#include <vector>

// 1. Use int64_t
// 2. Prefer ++i over i++
// 3. Simplify ternary operator

int main() {
  std::vector<int64_t> polynom(10, 2);
  std::vector<int64_t> odd;
  std::vector<int64_t> even;
  for (size_t i = 0; i < polynom.size(); ++i) {
    (i % 2 == 0 ? even : odd).emplace_back(polynom[i]);
  }
}
