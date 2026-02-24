#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// https://en.cppreference.com/w/cpp/iterator/reverse_iterator

template <class BidirIt>
class ReverseIterator {
  public:
    ReverseIterator() = default;
    explicit ReverseIterator(BidirIt it) : cur_(it) {}

    typename std::iterator_traits<BidirIt>::reference operator*() const {
        return *std::prev(cur_);
    }

    ReverseIterator& operator++() {
        --cur_;
        return *this;
    }
    ReverseIterator operator++(int) {
        auto res = *this;
        --(*this);
        return res;
    }

    ReverseIterator& operator--() {
        ++cur_;
        return *this;
    }
    ReverseIterator operator--(int) {
        auto res = *this;
        ++(*this);
        return res;
    }

    // Much more ...

  protected:
    BidirIt cur_;
};

////////////////////////////////////////////////////////////////////////////////

template <typename T>
void PrintVec(const std::vector<T>& vec) {
    for (const auto& elem : vec) {
        std::cout << elem << ' ';
    }
    std::cout << '\n';
}

// Add reverse iterators to vector

// 1 2 3 4 5
// ^         ^
// |         |

// *v.rbegin() = 5
// *(++v.rend()) = 1

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    std::sort(vec.rbegin(), vec.rend());
    PrintVec(vec);  // 5 4 3 2 1
    ++vec.rbegin();

    std::sort(vec.begin(), vec.end());
    auto mid = vec.begin() + vec.size() / 2;
    // auto rmid = std::make_reverse_iterator(mid); // until c++17
    auto rmid = std::reverse_iterator(mid);
    std::sort(vec.rbegin(), rmid);
    PrintVec(vec);  // 1 2 5 4 3

    auto rsorted_until = std::is_sorted_until(vec.rbegin(), vec.rend());
    std::cout << rsorted_until - vec.rbegin() << '\n';  // 3

    // std::cout << rsorted_until - vec.begin() << '\n'; // CE !!! explicit ctor
}
