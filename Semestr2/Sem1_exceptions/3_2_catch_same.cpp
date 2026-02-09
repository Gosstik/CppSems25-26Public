#include <cstdint>
#include <iostream>

// catch (int[]) { ... } is similar to catch (int*) { ... }

void SameType() {
    try {
        int64_t val = 1;
        throw val;
    } catch (int64_t) {
        std::cout << "1\n";
    } catch (int64_t) {  // Warning: exception will be caught by earlier handler
        std::cout << "2\n";
    }
}

// CE: ‘...’ handler must be the last handler for its try block
void DoubleEllipsis() {
    // Double ellipsis
    try {
        int64_t val = 1;
        throw val;
    } catch (...) {
        std::cout << "1\n";
    } catch (...) {
        std::cout << "2\n";
    }

    // Ellipsis at start
    try {
        int64_t val = 1;
        throw val;
    } catch (...) {
        std::cout << "1\n";
    } catch (int64_t) {
        std::cout << "2\n";
    }
}

int main() { SameType(); }
