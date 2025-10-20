#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

// 0. Name of function frequently starts with verb
// 1. Accept const vector&
// 2. number_of_digits == digits_count, always >= 0
// 3. if (i == 0) outside cycle
// 4. empty() instead size() == 0
// 5. vector.back() instead of vector[vector.size() - 1]
// 6. Prefer intermediate calculations over multi-line calculations
// 7. ++i instead of i++
// 8. Reuse result of operations

// or simply ToString(...)
std::string TransformToString(
    const std::vector<int64_t>& integer, size_t digits_pre_block_count) {
  std::string result;

  if (integer.empty()) {
    return result;
  }

  result += std::to_string(integer.back());

  for (size_t i = 1; i < integer.size(); ++i) {
    int64_t cur_block = integer[integer.size() - i - 1];
    std::string cur_block_str = std::to_string(cur_block);

    size_t active_digits_count = cur_block_str.size();
    size_t nulls_count = digits_pre_block_count - active_digits_count;

    result += std::string(nulls_count, '0');
    result += cur_block_str;
  }

  return result;
}

int main() {}
