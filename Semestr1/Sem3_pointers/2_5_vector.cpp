#include <iostream>
#include <vector>

int main() {
    std::vector<int> v = {1, 2, 3, 4, 5};
    int* p0 = &v[0];
    int* p3 = &v[3];
    std::cout << p0 - p3 << '\n';  // 3
    std::cout << *p0 << '\n';      // 1

    // Another way
    int* pv0 = v.data();
    int* pv3 = v.data() + 3;
    // ...
}
