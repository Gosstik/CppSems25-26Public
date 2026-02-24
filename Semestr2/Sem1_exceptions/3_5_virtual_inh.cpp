#include <iostream>

struct Granny {
    int g;
};

// struct Mom : Granny {
//     int m;
// };

// struct Dad : Granny {
//     int d;
// };

struct Mom : virtual Granny {
    int m;
};

struct Dad : virtual Granny {
    int d;
};

struct Son : Mom, Dad {
    int s;
};

int main() {
    try {
        throw Son{};  // NOLINT
    } catch (const Granny& obj) {
        std::cout << "Granny\n";
    } catch (...) {
        std::cout << "...\n";
    }
}
