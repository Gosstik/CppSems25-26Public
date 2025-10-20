#include <cstdint>
#include <iostream>

namespace my_ns {

bool IsZero(int func_param) {
    return func_param == 0;
}

const int kGlobalValue = 10;

// same for class
struct CustomStruct {
public:
    typedef uint64_t SizeType1;
    using SizeType2 = uint64_t;

    int players_count = 10;
    int GetPlayersCount() {
        return players_count;
    }

private:

    int GetImplField() {
        return impl_field_;
    }

    int impl_field_ = 1;
};

}  // namespace my_ns

int main() {
    std::cout << my_ns::kGlobalValue << '\n';
}
