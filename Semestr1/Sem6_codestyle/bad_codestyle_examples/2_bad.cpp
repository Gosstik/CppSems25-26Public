#include <cstddef>
#include <cstdint>
#include <vector>

#define MAX_BLOCK_VALUE 1000

std::vector<int64_t> UpdateBlocks(
    std::vector<int64_t> block, size_t last, bool negative, int64_t coef) {
  for (size_t i = 0; i + 1 < last || negative; ++i) {
    if (block[i] >= MAX_BLOCK_VALUE) {
      block[i + 1] += block[i] / MAX_BLOCK_VALUE;
      block[i] %= MAX_BLOCK_VALUE;
    }
    if (block[i] < 0) {
      coef = (-block[i] + MAX_BLOCK_VALUE - 1) / MAX_BLOCK_VALUE;
      block[i + 1] -= coef;
      block[i] += coef * MAX_BLOCK_VALUE;
    }

    if (block[i + 1] < 0)
      negative = true;
    else
      negative = false;
  }

  return block;
}

int main() {}
