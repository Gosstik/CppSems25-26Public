#include <type_traits>
#include <vector>

// Aliases does not comply to common rules of template substitution.
// Actually, alias does not define template id.
// !!! Therefore, we cannot specialize aliases.
// !!! CTAD is still working

// OK
template <typename T>
using Vec = std::vector<T>;

// CE
template <>
using Vec<int> = std::vector<int>;

int main() {
    std::vector v1 = {1, 2, 3, 4};  // OK, CTAD
    Vec v2 = {1, 2, 3, 4};          // OK, CTAD for alias templates
}
