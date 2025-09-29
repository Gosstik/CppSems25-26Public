#include <iostream>
#include <sys/resource.h>

int main() {
    const rlim_t kStackSize = 16 * 1024 * 1024;   // min stack size = 16 MB
    struct rlimit rl{};
    int result;

    result = getrlimit(RLIMIT_STACK, &rl);
    if (result != 0) {
        std::cerr << "Failed to get current stack size\n";
        abort();
    }

    std::cout << "Initial stack size: " << rl.rlim_cur << '\n';

    if (rl.rlim_cur < kStackSize) {
        rl.rlim_cur = kStackSize;
        result = setrlimit(RLIMIT_STACK, &rl);
        if (result != 0) {
            std::cerr << "Failed to set bigger stack size\n";
            abort();
        }
        std::cerr << "Stack size is successfully set to " << kStackSize << '\n';
    }
}
