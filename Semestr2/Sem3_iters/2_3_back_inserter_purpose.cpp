#include <algorithm>
#include <iterator>
#include <vector>

// Later (before c++17) there was not CTAD and deduction guides and
// std::back_inserter allowed omit template parameter (Container) in
// call. Now it is convenient as it consists of less letters.

// Try to compile with 14 ans 17 standards.

int main() {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2;

    // CE until c++17
    std::copy(v1.begin(), v1.end(), std::back_insert_iterator(v2));

    //// Always compiles

    // std::copy(
    //     v1.begin(), v2.end(), std::back_insert_iterator<std::vector<int>>(v2)
    // );

    std::copy(v1.begin(), v1.end(), std::back_inserter(v2));
}
