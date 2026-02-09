#include <iostream>

// Memory layout:
// 1) Without Granny: m d s
// 2) With Granny: g m g d s, sizeof(Son) == 20

// How cast to Dad is working?

struct Granny {
    int g;
};
struct Mom : Granny {
    int m;
};
struct Dad : Granny {
    int d;
};

// Diamond problem
struct Son : Mom, Dad {
    int s;
};

void MomFn(Mom& m) {
    std::cout << "Mom address: " << &m << '\n';
}
void DadFn(Dad& d) {
    std::cout << "Dad address: " << &d << '\n';
}

int main() {
    Son s;
    std::cout << "Son address: " << &s << '\n';
    MomFn(s);
    DadFn(s);
}
