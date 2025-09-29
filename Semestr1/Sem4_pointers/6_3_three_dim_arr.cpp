#include <iostream>

void ThreeDimArr1(int a[][3][5], size_t height) {
    std::cout << "Print 3 dim array:\n";
}

//// CE
// void ThreeDimArr2(int a[3][][5], size_t height);

//// CE
// void ThreeDimArr3(int a[3][5][], size_t height);

int main() {
    // 3 dim array
    int c[10][3][5] = {};
    ThreeDimArr1(c, 10);
}
