#include <cassert>
#include <forward_list>
#include <iostream>
#include <iterator>
#include <list>
#include <vector>

namespace detail {

template <typename InputIt, typename Distance>
void AdvanceImpl(InputIt& it, Distance n, std::input_iterator_tag /*unused*/) {
    assert(n >= 0);
    while (n > 0) {
        ++it;
        --n;
    }
}

template <typename InputIt, typename Distance>
void AdvanceImpl(
    InputIt& it, Distance n, std::bidirectional_iterator_tag /*unused*/
) {
    if (n > 0) {
        while (n > 0) {
            ++it;
            --n;
        }
        return;
    }

    while (n < 0) {
        --it;
        ++n;
    }
}

template <typename InputIt, typename Distance>
void AdvanceImpl(
    InputIt& it, Distance n, std::random_access_iterator_tag /*unused*/
) {
    std::cout << "Fast impl\n";
    it += n;
}

}  // namespace detail

template <typename InputIt, typename Distance>
void Advance(InputIt& it, Distance n) {
    detail::AdvanceImpl(
        it, n, typename std::iterator_traits<InputIt>::iterator_category{});
}

int main() {
    std::forward_list<int> fl = {1, 2, 3, 4, 5};
    auto fl_it = fl.begin();
    Advance(fl_it, 4);
    std::cout << "forward_list[4]: " << *fl_it << '\n';
    // Advance(fl_it, -4);  // RE

    std::list<int> l = {1, 2, 3, 4, 5};
    auto l_it = l.begin();
    Advance(l_it, 4);
    std::cout << "list[4]: " << *l_it << '\n';
    Advance(l_it, -4);
    std::cout << "list[0]: " << *l_it << '\n';

    std::vector<int> vec = {1, 2, 3, 4, 5};
    auto vec_it = vec.begin();
    Advance(vec_it, 4);
    std::cout << "vector[4]: " << *vec_it << '\n';
    Advance(vec_it, -4);
    std::cout << "vector[0]: " << *vec_it << '\n';
}
