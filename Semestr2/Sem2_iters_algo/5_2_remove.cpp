#include <iostream>
#include <iterator>
#include <vector>

// Copy from previous
template <typename InputIt, typename UnaryPredicate>
InputIt FindIf(InputIt first, InputIt last, UnaryPredicate pred) {
    for (; first != last; ++first) {
        if (pred(*first)) {
            return first;
        }
    }

    return last;
}

////////////////////////////////////////////////////////////////////////////////

template <typename T>
struct EqualToUnaryPredicate {
    explicit EqualToUnaryPredicate(const T& value) : init_value(value) {}

    bool operator()(const T& value) const
        noexcept(noexcept(init_value == value)) {
        return init_value == value;
    }

    T init_value;
};

template <
    typename ForwardIt,
    typename T = typename std::iterator_traits<ForwardIt>::value_type>
ForwardIt Remove(ForwardIt first, ForwardIt last, const T& value) {
    // avoid extra copy
    auto res_end = FindIf(first, last, EqualToUnaryPredicate(value));
    if (res_end == last) {
        return res_end;
    }
    for (auto it = res_end; it != last; ++it) {
        if (*it != value) {
            *res_end = *it;
            ++res_end;
        }
    }
    return res_end;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    std::vector<int> vec{1, 2, 2, 5, 2, 9};
    auto new_end = Remove(vec.begin(), vec.end(), 2);
    for (auto it = vec.begin(); it != new_end; ++it) {
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}
