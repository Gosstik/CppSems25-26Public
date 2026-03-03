#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// std:istream_iterator
// https://en.cppreference.com/w/cpp/iterator/istream_iterator

// istream is Input, but not Forward iterator

int main() {
    std::cout << "1\n";
    std::istream_iterator<int> it(std::cin);
    std::cout << "2\n";  // will be waiting input to construct it
    std::vector<int> v;

    //// Option 1
    // for (int i = 0; i < 5; ++i, ++it) {
    //     v.push_back(*it); // std::cin >> val;
    // }

    //// Option 2
    std::copy(it, std::istream_iterator<int>(), std::back_inserter(v));

    //// Option 3
    // std::copy_n(it, 5, std::back_inserter(v));

    //// Option 4
    // std::vector<int> v(it, std::istream_iterator<int>()); // the easiest way

    //// Print
    for (auto val : v) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}
