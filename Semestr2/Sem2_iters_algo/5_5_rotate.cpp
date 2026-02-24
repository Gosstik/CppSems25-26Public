#include <algorithm>
#include <iostream>
#include <vector>

template <typename T>
void PrintVec(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5, 6};
    auto first = vec.begin();
    auto mid = vec.begin() + 2;
    auto last = vec.end();

    auto res = std::rotate(first, mid, last);
    std::vector<int> res_vec(first, last);  // order of iters didn't change
    PrintVec(res_vec);                      // 3 4 5 6 1 2

    std::vector<int> mid_seq(mid, last);  // mid also didn't change
    PrintVec(mid_seq);                    // 5 6 1 2

    std::vector<int> res_seq(res, last);
    PrintVec(res_seq);  // 1 2
}
