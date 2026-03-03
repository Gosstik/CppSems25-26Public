#include <algorithm>
#include <cassert>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

// How to test SortSolver ???

void SortSolver() {
    size_t n{};
    std::cin >> n;
    std::vector<int> vec(n, -1);
    for (size_t i = 0; i < n; ++i) {
        std::cin >> vec[i];
    }

    std::sort(vec.begin(), vec.end());

    for (auto val : vec) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}

////////////////////////////////////////////////////////////////////////////////

template <typename Cleaner>
struct Defer {
    explicit Defer(Cleaner cleaner) : cleaner(cleaner) {}
    void Call() {
        assert(!called);
        called = true;
        cleaner();
    }
    ~Defer() {
        if (!called) {
            cleaner();
        }
    }

    Cleaner cleaner;
    bool called = false;
};

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

    // Spoof buffers
    std::streambuf* cin_rdbuf = std::cin.rdbuf(iss.rdbuf());
    ;  // remember std::cin's old state
    std::streambuf* cout_rdbuf =
        std::cout.rdbuf(ss.rdbuf());  // remember std::cin's old state

    // Bring buffers back with raii
    Defer bring_back_buffers([&cin_rdbuf, &cout_rdbuf]() {
        std::cin.rdbuf(cin_rdbuf);
        std::cout.rdbuf(cout_rdbuf);
    });

    // Call solution
    SortSolver();

    // Test output
    std::vector<int> actual(
        std::istream_iterator<int>(ss), std::istream_iterator<int>{});
    if (actual != expected) {
        bring_back_buffers.Call();
        std::cout << "----Test failed----\n";
        std::cout << "expected: ";
        PrintVec(expected);
        std::cout << "actual: ";
        PrintVec(actual);
        return false;
    }

    bring_back_buffers.Call();
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
