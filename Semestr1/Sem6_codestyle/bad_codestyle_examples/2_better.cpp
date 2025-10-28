#include <cstddef>
#include <cstdint>
#include <vector>

// 1. No defines
// 2. Pass vector by reference (and return)
// 3. Vector variables should be named in plural in most cases
// 4. bool predicate should have prefix is/has/can
// 5. Curly braces for one line for/if/else
// 6. Boolean expressions often can be simplified
// 7. Precedence of operations in for

static const int64_t kMaxBlockValue = 1000;

void UpdateBlocks(std::vector<int64_t>& blocks, size_t last, int64_t coef) {
  bool is_negative = false;

  for (size_t i = 0; (i + 1 < last) || is_negative; ++i) {
    if (blocks[i] >= kMaxBlockValue) {
      blocks[i + 1] += blocks[i] / kMaxBlockValue;
      blocks[i] %= kMaxBlockValue;
    }
    if (blocks[i] < 0) {
      coef = (-blocks[i] + kMaxBlockValue - 1) / kMaxBlockValue;
      blocks[i + 1] -= coef;
      blocks[i] += coef * kMaxBlockValue;
    }

    is_negative = blocks[i + 1] < 0;
  }
}

int main() {}
