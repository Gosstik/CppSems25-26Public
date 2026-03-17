#include <algorithm>
#include <vector>

int main() {
    std::vector<int> v = {1, 9, 2, 4, 8, 6};
    std::sort(v.begin(), v.end());
    std::ranges::sort(v);  // how many args/template arguments/overloadings
}
