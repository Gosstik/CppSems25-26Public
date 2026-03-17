#include <vector>
#include <iostream>

// Written logic is hard to read and understand.
// In practice it is far more difficult.
// A good practice is to decompose that logic to several independent blocks.

int main() {
    std::vector<int> vec = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    std::vector<int> result;
    for (auto n: vec) {
        if (n % 2 == 0) {
            result.push_back(n * n);
        }
        if (result.size() == 3) {
            break;
        }
    }

    for (auto n: result) {
        std::cout << n << " ";
    }
}
