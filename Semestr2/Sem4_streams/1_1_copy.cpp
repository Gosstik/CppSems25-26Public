#include <algorithm>
#include <vector>

int main() {
    std::vector<int> vec(5, 1);
    int arr[5]{};
    std::copy(vec.begin(), vec.end(), arr);  // OK
}
