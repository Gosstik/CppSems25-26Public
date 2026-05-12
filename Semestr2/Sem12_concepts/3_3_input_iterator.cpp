#include <concepts>
#include <iterator>
#include <vector>

// TODO: abstract classes (e.g. contains(range, value))
// Concept --- a way to combine requirements within a named entity

template <typename T>
concept InputIterator = requires(T it) {
    { ++it } -> std::same_as<T&>;
    typename std::iterator_traits<T>::value_type;
    {
        *it
    } -> std::convertible_to<typename std::iterator_traits<T>::value_type>;
};

template <typename It, typename Predicate>
    requires InputIterator<It> && requires(Predicate p, It it) { p(*it); }
It FindIf1(It beg, It end, Predicate p) {
    for (auto it = beg; it != end; ++it) {
        if (p(*it)) {
            return it;
        }
    }
    return end;
}

// Shorter version
template <
    InputIterator It,
    std::predicate<decltype(*std::declval<It>())> Predicate>
It FindIf2(It beg, It end, Predicate p) {
    for (auto it = beg; it != end; ++it) {
        if (p(*it)) {
            return it;
        }
    }
    return end;
}

// Version without template
void GetValue(InputIterator auto it) { return *it; }

//// Same as above
template <InputIterator It>
void GetValue(It it) {
    return *it;
}

int main() {
    std::vector<int> vec{1, 2, 3, 4, 5};
    FindIf1(vec.begin(), vec.end(), [](int i) {
        return i % 2 == 0;
    });
}
