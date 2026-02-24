#include <iostream>
#include <vector>

int main() {
    std::vector<int> vi{1, 5, 4, 6};
    for (auto& val : vi) { // OK
        val = 1;
    }

    std::vector<bool> vb{true, true, false, true};
    for (auto& val : vb) { // CE (a temporary of type std::_Bit_reference)
        val = false;
        std::cin >> val; // CE
    }

    std::vector<bool> vb2{true, true};
    for (auto val : vb2) { // CE (a temporary of type std::_Bit_reference)
        bool tmp{};
        std::cin >> tmp; // CE
        val = tmp;
    }
    std::cout << vb2[0] << '\n';
}
