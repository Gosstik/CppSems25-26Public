#include <algorithm>
#include <iterator>
#include <vector>

// std::sort does not have requirements yet, body is not instantiated

template <typename T>
    requires std::
        is_base_of_v<std::input_iterator_tag, typename T::iterator_category>
    void MySort(T first, T last) {}

template <typename T>
    // requires requires(T a, T b) { std::sort(a, b); }  // 1
    // requires requires(T a, T b) { MySort(a, b); } // 2
void Foo(T first, T last) {
    // std::sort(first, last);
}

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    Foo(v.begin(), v.end());  // OK with both 1 and 2
    Foo(1, 2);                // OK with 1, CE with 2
}
