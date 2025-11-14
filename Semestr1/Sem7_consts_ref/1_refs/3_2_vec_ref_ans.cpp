#include <iostream>
#include <vector>

// OK, CE, RE, UB ???

int main() {
    // std::vector<int> a;
    //* vector stores pointer to data, but type int&* does not exist
    std::vector<int&> a;

    int x = 0;
    int y = 1;
    a.push_back(x);
    a.push_back(y);

    int& s = a[0];
    int t = a[1];

    std::vector<int>& b = a;
    b[0] = 2;
    b[1] = 3;

    std::cout << s << t << a[0] << a[1] << '\n';  // 2123
}
