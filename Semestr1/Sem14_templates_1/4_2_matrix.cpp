#include <iostream>

template <size_t M, size_t N, typename Field = double>
class Matrix {};

template <size_t N, typename Field = double>
using SquareMatrix = Matrix<N, N, Field>;

template <size_t M, size_t K, size_t N, typename Field = double>
Matrix<M, N, Field> operator*(
    const Matrix<M, K, Field>& lhs, const Matrix<K, N, Field>& rhs) {
    // ...
}

int main() {
    {
        Matrix<5, 5> m;
        SquareMatrix<5> sm;

        auto res = m * sm;
    }
}
