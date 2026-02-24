#include <array>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <type_traits>
#include <vector>

template <typename InputIt>
typename std::iterator_traits<InputIt>::difference_type Distance(
    InputIt first, InputIt last) {
    using IterTag = typename std::iterator_traits<InputIt>::iterator_category;
    if constexpr (std::is_same_v<IterTag, std::random_access_iterator_tag>) {
        std::cout << "Fast way\n";
        return last - first;
    }

    // if constexpr (std::is_base_of_v<std::random_access_iterator_tag,
    // IterTag>)
    // {
    //   std::cout << "Fast way\n";
    //   return last - first;
    // }

    typename std::iterator_traits<InputIt>::difference_type res = 0;
    while (first != last) {
        ++res;
        ++first;
    }
    return res;
}

// iterator_concept is defined only for std::iterator_traits<T*>
static_assert(std::is_same_v<
              typename std::iterator_traits<int*>::iterator_category,
              std::random_access_iterator_tag>);

static_assert(std::is_same_v<
              typename std::iterator_traits<int*>::iterator_concept,
              std::contiguous_iterator_tag>);

int main() {
    std::forward_list<int> fl = {1, 2, 3, 4, 5};
    auto fl_res = Distance(fl.begin(), fl.end());
    std::cout << "forward_list: " << fl_res << '\n';

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto vec_res = Distance(vec.begin(), vec.end());
    std::cout << "vector: " << vec_res << '\n';

    std::array<int, 5> arr = {1, 2, 3, 4, 5};
    auto arr_res = Distance(arr.begin(), arr.end());
    std::cout << "array: " << arr_res << '\n';
}
