#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

// How to test SortSolver ???

void SortSolver(std::istream& in, std::ostream& out) {
    size_t n{};
    in >> n;
    std::vector<int> vec(n, -1);
    for (size_t i = 0; i < n; ++i) {
        in >> vec[i];
    }

    std::sort(vec.begin(), vec.end());

    for (auto val : vec) {
        out << val << ' ';
    }
    out << '\n';
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void PrintVec(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

bool TestSortSolver(
    const std::string& input, const std::vector<int>& expected) {
    std::istringstream iss(input);
    std::stringstream ss;

    // Call solution
    SortSolver(iss, ss);

    // Test output
    std::vector<int> actual(
        std::istream_iterator<int>(ss), std::istream_iterator<int>{});
    if (actual != expected) {
        std::cout << "----Test failed----\n";
        std::cout << "expected: ";
        PrintVec(expected);
        std::cout << "actual: ";
        PrintVec(actual);
        return false;
    }

    std::cout << "----Test passed!!!----\n";
    return true;
}

int main() {
    const std::string input = R"(
  4
  3 4 1 2
  )";

    std::vector<int> correct_expected{1, 2, 3, 4};
    std::vector<int> smaller_expected{1, 2, 3};
    std::vector<int> bigger_expected{1, 2, 3, 4, 5};

    TestSortSolver(input, correct_expected);
    TestSortSolver(input, smaller_expected);
    TestSortSolver(input, bigger_expected);
}
