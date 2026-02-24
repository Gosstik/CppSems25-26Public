#include <iostream>
#include <vector>

int main() {
    std::vector<int> v1{1, 2, 3};
    std::vector<int> v2(v1.begin(), v1.end());

    std::vector<char> vc{'a', 'b', 'c'};
    std::vector<char> vc2(vc.begin(), vc.end());

    const char* c1 = ";";
    const char* c2 = ",";
    // std::vector<char> vec(c2, c1);
    std::vector<char> vec(c1, c2);
    for (auto elem : vec) {
        std::cout << elem << '\n';
    }
}
