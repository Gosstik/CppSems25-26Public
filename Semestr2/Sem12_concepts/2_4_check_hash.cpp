#include <unordered_map>

template <typename T>
    requires requires() {
        // always true because hash is a template (it is not instantiated)
        typename std::hash<T>;
        // correct check
        std::hash<T>()(std::declval<T>());
    }
void Test() {}

int main() {
    Test<int>();   // OK
    Test<void>();  // CE
}
