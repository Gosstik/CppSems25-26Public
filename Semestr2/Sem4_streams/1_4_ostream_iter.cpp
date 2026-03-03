#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>

// std:ostream_iterator
// https://en.cppreference.com/w/cpp/iterator/ostream_iterator

// output_iterator has no operator==, so there is no end !!!

int main() {
    //// Option 1
    // std::istream_iterator<int> in_it(std::cin);

    //// Option 2
    std::ifstream input = std::ifstream("input.txt");
    std::istream_iterator<int> in_it(input);

    //////////////////////////////////////////////////////////////////////////////

    //// case 1
    // std::copy(
    //     in_it,
    //     std::istream_iterator<int>(),
    //     std::ostream_iterator<int>(std::cout, " "));

    //// case 2
    // std::copy_if(
    //     in_it,
    //     std::istream_iterator<int>(),
    //     std::ostream_iterator<int>(std::cout, " "),
    //     [](int a) {
    //       return a % 2 == 0;  // even
    //     }
    // );

    //// case 3
    // std::transform(
    //     in_it,
    //     std::istream_iterator<int>(),
    //     std::ostream_iterator<int>(std::cout, " "),
    //     [](int a) {
    //       return a * a;
    //     }
    // );

    std::cout << '\n';
}
