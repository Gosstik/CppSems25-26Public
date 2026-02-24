#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// Impl with reverse iterator:
// https://en.cppreference.com/w/cpp/algorithm/next_permutation#Possible_implementation

template <typename BidirIt>
bool NextPermutation(BidirIt first, BidirIt last) {
    if (first == last) {
        return false;
    }

    auto break_sort_it = std::prev(last);
    while (break_sort_it != first) {
        auto prev = break_sort_it--;  // ..., break_sort_it, prev, ...
        if (*break_sort_it < *prev) {
            break;
        }
    }

    const typename std::iterator_traits<BidirIt>::reference break_sort_val =
        *break_sort_it;

    // upper_bound
    auto upper_it = std::prev(last);
    for (; !(break_sort_val < *upper_it) && upper_it != break_sort_it;
         --upper_it) {
    }
    // break_sort_it == upper_it only when array is sorted in descending order
    if (break_sort_it != upper_it) {
        std::swap(*break_sort_it, *upper_it);
        ++break_sort_it;
    }

    std::reverse(break_sort_it, last);
    return break_sort_it != first;
}

////////////////////////////////////////////////////////////////////////////////

// Tests

template <typename T>
void PrintVec(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

void Test(const char* test_name, std::vector<int> vec) {
    std::cout << "----" << test_name << "----\n";
    size_t total = vec.size() != 0;
    PrintVec(vec);
    while (NextPermutation(vec.begin(), vec.end())) {
        PrintVec(vec);
        ++total;
    }
    std::cout << "total=" << total << '\n';
}

int main() {
    Test("Empty", {});
    Test("One", {1});
    Test("Two", {1, 2});
    Test("Three", {1, 2, 3});
    Test("Five", {1, 2, 3, 4, 5});
    Test("Equals", {1, 2, 2, 3, 3});
}
