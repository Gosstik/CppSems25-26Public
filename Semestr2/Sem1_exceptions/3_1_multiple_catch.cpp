#include <cstdint>
#include <iostream>

// Only exact match (const and & may be added) or cast to Parent is acceptable.

template <typename T>
void GtoP(T to_throw) {
    try {
        throw to_throw;  // NOLINT
    } catch (double d) {
        std::cout << "double\n";
    } catch (int64_t i) {
        std::cout << "int64_t\n";
    } catch (uint32_t i) {
        std::cout << "uint32_t\n";
    } catch (...) {
        std::cout << "...\n";
    }
}

int main() {
    GtoP<int32_t>(1);
    GtoP<float>(1.0f);
}
