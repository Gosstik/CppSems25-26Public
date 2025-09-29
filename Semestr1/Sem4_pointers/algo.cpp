#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <deque>
#include <iostream>
#include <numeric>  // iota
#include <vector>

// void Bar(int64_t val) {
//   std::cout << val * 2;
// }

// void Bar(uint64_t val) {
//   std::cout << val * 2;
// }

// template <typename T>
// int Func(T val) {
//   return val * 2;
// }

// int main() {
//   std::cout << Func(2) << '\n';
//   std::cout << Func<uint32_t>(4) << '\n';
// }

template <typename T>
void PrintVec(std::vector<T>& vec) {
  for (auto val : vec) {
    std::cout << val << " ";
  }
  std::cout << "\n";
}

void IotaExample() {
  // 1
  std::vector<int64_t> vec(11);
  std::iota(vec.begin(), vec.end(), -5);
  PrintVec(vec);

  //////////////////////////////////////////////////////////////////////////////

  // 2
  auto mid = vec.begin() + vec.size() / 2;
  std::iota(vec.begin(), mid, 1);
  std::iota(mid, vec.end(), 10);
  PrintVec(vec);

  //////////////////////////////////////////////////////////////////////////////

  // 3
  // ? CE, UB, ...
  std::vector<int64_t> vec2;
  std::iota(vec2.begin(), vec2.end(), -5);
  PrintVec(vec2);

  //////////////////////////////////////////////////////////////////////////////

  // 4
  int64_t arr[10] = {};
  std::iota(arr, arr + 10, 1);
  PrintVec(vec);
}

// ##############################################################################

void FillExample() {
  size_t n = 8;

  std::vector<int64_t> vec(n, -1);
  auto mid = vec.begin() + n / 2;
  std::fill(mid, vec.end(), 1);
  PrintVec(vec);
}

// ##############################################################################

void ReverseExample() {
  // sort without comp
  std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8};
  std::reverse(vec.begin(), vec.end());
  PrintVec(vec);
}

// ##############################################################################

void CopyExample() {
  std::vector<int64_t> vec(6, 7);
  std::fill(vec.begin() + vec.size() / 2, vec.end(), -1);
  std::reverse(vec.begin(), vec.end());

  std::vector<int64_t> vec2(vec);
  PrintVec(vec2);

  // std::deque<int64_t> deq(vec);
  std::deque<int64_t> deq;  // ! Resize
  // int64_t array[3] = {1, 3, 4};
  std::copy(vec.begin(), vec.end(), deq.begin());
  for (auto val : deq) {
    std::cout << val << ' ';
  }
  std::cout << '\n';
}

// ##############################################################################

void AllOfExample() {
  // TODO
}

// ##############################################################################

void UniqueExample() {
  // TODO
}

// ##############################################################################

int main() {
  IotaExample();
  // FillExample();
  // ReverseExample();
  // CopyExample();
  // AllOfExample();
  // UniqueExample();
}
