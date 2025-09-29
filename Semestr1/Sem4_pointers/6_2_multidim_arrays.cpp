#include <iostream>
#include <vector>

void PrintMatrix(int a[][3], size_t height) {
    // a[i][j] == *(a + i * 3 + j)
    std::cout << "Print matrix:\n";
    for (size_t i = 0; i < height; ++i) {
        for (size_t j = 0; j < 5; ++j) {
            std::cout << a[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

//// CE: all dimensions except the outer one should have fixed size
// void PrintMatrix(int a[][], size_t height);

void PrintMatrix(const std::vector<std::vector<int>>& vv) {
    // a[i][j] == *(a + i * 3 + j)
    std::cout << "Print matrix:\n";
    for (size_t i = 0; i < vv.size(); ++i) {
        for (size_t j = 0; j < vv[i].size(); ++j) {
            std::cout << vv[i][j] << ' ';
        }
        std::cout << '\n';
    }
    std::cout << '\n';
}

int main() {
    int a[5][3] = {};
    PrintMatrix(a, 5);

    int b[][3] = {{1, 2, 3}, {4, 5, 6}};
    PrintMatrix(b, 5);

    //// CE
    // int c[3][5] = {};
    // PrintMatrix(c, 5);

    //// CE
    // int d[][] = {};

    // 2 dim vector
    std::vector<std::vector<int>> vv({{1, 2, 3}, {4, 5}});
    PrintMatrix(vv);
}
