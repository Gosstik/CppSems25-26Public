#include <iostream>
#include <vector>

// Predicate is better to be a separate template parameter.

template <typename InputIt>
InputIt FindIf(
    InputIt first,
    InputIt last,
    bool (*pred)(typename std::iterator_traits<InputIt>::value_type)) {
    for (; first != last; ++first) {
        if (pred(*first)) {
            return first;
        }
    }

    return last;
}

template <typename T>
bool EvenUnaryPredicate(const T val) {
    return val % 2 == 0;
}

int main() {
    std::vector<int> vec{1, 5, 2, 4, 9, 8};
    for (auto it = vec.begin(); true; ++it) {
        it = FindIf(it, vec.end(), EvenUnaryPredicate);
        if (it == vec.end()) {
            break;
        }
        std::cout << *it << ' ';
    }
    std::cout << '\n';
}
