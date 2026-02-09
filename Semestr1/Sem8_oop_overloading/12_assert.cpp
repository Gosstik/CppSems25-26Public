#include <iostream>

// Uncomment for Release version
#define NDEBUG

////////////////////////////////////////////////////////////////////////////////

// Assertions

// Unreachable by control flow
#define TOOLBOX_UNREACHABLE() std::abort()

#ifndef NDEBUG

#define TOOLBOX_ASSERT(cond, error)                     \
    do {                                                \
        if (!(cond)) {                                  \
            std::cerr << "Toolbox assertion '" << #cond \
                      << "' failed: " << error << '\n'; \
            TOOLBOX_UNREACHABLE();                      \
        }                                               \
    } while (false)

#define TOOLBOX_VERIFY(cond, error)                                           \
    do {                                                                      \
        if (!(cond)) {                                                        \
            std::cerr << "Toolbox verify '" << #cond << "' failed: " << error \
                      << '\n';                                                \
        }                                                                     \
    } while (false)

#else

#define TOOLBOX_ASSERT(cond, error) (void)nullptr

#define TOOLBOX_VERIFY(cond, error) (void)nullptr

#endif

////////////////////////////////////////////////////////////////////////////////

// Poor implementation for release version

#define FAKE_ASSERT(cond, error) (void)(cond)

////////////////////////////////////////////////////////////////////////////////

struct S {
    int val;

    S operator+(const S& other) const {
        std::cout << "CALLED +\n";
        return {val + other.val};
    }

    operator int() const {  // for comparison
        return val;
    }
};

int main() {
    [[maybe_unused]] S a(1);
    [[maybe_unused]] S b(2);

    TOOLBOX_ASSERT(a < a + b, "Processor is broken...");
    // FAKE_ASSERT(a < a + b, "Evaluates even if cond is not used!!!");
}
