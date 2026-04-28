#include <vector>

// template <typename Container>
// auto& GetElementLong(Container& c, size_t i) {
//     return c[i];
// }

template <typename Container>
auto GetElementLong(Container& c, size_t i) -> decltype(c[i]) {
    return c[i];
}

// since c++14
template <typename Container>
decltype(auto) GetElement(Container& c, size_t i) {
    return c[i];
}

template <typename Container>
decltype(auto) GetElementAdvanced(Container& c, size_t i) {
    decltype(auto) val = c[i];
    // return (val); // invalid for rvalue
    return val;
}

template <typename T>
void Debug() = delete;

int main() {
    std::vector<int> vi(3, 1);
    auto ie = GetElement(vi, 1);
    // Debug<decltype(ie)>(); // int&

    std::vector<bool> vb(3, true);
    auto be = GetElement(vb, 1);
    // Debug<decltype(be)>(); // std::_Bit_reference

    decltype(auto) val = ie;  // decltype(auto) not only in return type
}
