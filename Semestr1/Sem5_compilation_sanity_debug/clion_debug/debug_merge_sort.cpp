#include <iostream>
#include <vector>

// Given array of N integers
// For each element output number of elements < it that are placed to the left of it

// Input:
// 6
// 6 2 5 4 3 1

// Output
// 5 1 3 2 1 0

template <typename T>
struct Node {
  T val;
  size_t pos;  // pos of val after getting array
};

template <typename T>
void Merge(
    std::vector<Node<T>>& left_arr,
    std::vector<Node<T>>& right_arr,
    std::vector<Node<T>>& res,
    std::vector<size_t>& invs) {
  size_t left = 0;
  size_t right = 0;
  size_t cur = 0;
  while (left < left_arr.size() && right < right_arr.size()) {
    if (left_arr[left].val <= right_arr[right].val) {
      invs[left_arr[left].pos] += right;
      res[cur++] = left_arr[left++];
    } else {
      res[cur++] = right_arr[right++];
    }
  }
  while (left < left_arr.size()) {
    invs[left_arr[left].pos] += right;
    res[cur++] = left_arr[left++];
  }
  while (right < right_arr.size()) {
    res[cur++] = right_arr[right++];
  }
}

template <typename T>
void MergeSortWithInversions(
    std::vector<Node<T>>& arr, std::vector<size_t>& invs) {
  if (arr.size() < 2) {
    // call stack and backtrace
    return;
  }
  std::vector<Node<T>> left_arr(arr.size() / 2);
  for (size_t i = 0; i < left_arr.size(); ++i) {
    left_arr[i] = arr[i];
  }
  MergeSortWithInversions(left_arr, invs);
  std::vector<Node<T>> right_arr(arr.size() - left_arr.size());
  for (size_t i = 0; i < right_arr.size(); ++i) {
    right_arr[i] = arr[i + left_arr.size()];
  }
  MergeSortWithInversions(right_arr, invs);
  Merge(left_arr, right_arr, arr, invs);
}

class Solver {
 public:
  void DoIt() {
    std::cin >> n;
    std::vector<Node<int64_t>> arr(n);
    for (size_t i = 0; i < n; ++i) {
      std::cin >> arr[i].val;
      arr[i].pos = i;
    }
    std::vector<size_t> invs(n, 0);
    MergeSortWithInversions(arr, invs);
    for (auto& elem : invs) {
      std::cout << elem << " ";
    }
  }

  size_t n = 0;
};

int main() {
  std::ios_base::sync_with_stdio(false);
  std::cin.tie();
  std::cout.tie();

  Solver solver;
  solver.DoIt();
}
