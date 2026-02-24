#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// std::front_inserter
// std::inserter (insert by given iterator)

bool IsEven(int val) noexcept { return val % 2 == 0; }

template <typename Container>
class BackInsertIterator {
  public:
    using iterator_category = std::output_iterator_tag;  // NOLINT

    // other usings...

    BackInsertIterator(Container& container)
        : container_(container) {}  // NOLINT

    BackInsertIterator& operator=(const typename Container::value_type& val) {
        container_.push_back(val);
        return *this;
    }

    BackInsertIterator& operator++() { return *this; }

    BackInsertIterator& operator*() { return *this; }

  private:
    Container& container_;
};

template <typename Container>
BackInsertIterator<Container> BackInserter(Container& container) {
    return {container};
}

int main() {
    int a[10] = {1, 2, 3, 4, 5};
    std::vector<int> v;

    //// general way
    // std::copy_if(
    //     a, a + 10, std::back_insert_iterator<std::vector<int>>(v), IsEven
    // );

    //// template parameter can be omitted
    // std::copy_if(
    //     a, a + 10, std::back_insert_iterator(v), IsEven
    // );

    //// back_inserter for simplicity
    // std::copy_if(a, a + 10, std::back_insert_iterator(v), IsEven);
    std::copy_if(a, a + 10, std::back_inserter(v), IsEven);

    for (auto val : v) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}
