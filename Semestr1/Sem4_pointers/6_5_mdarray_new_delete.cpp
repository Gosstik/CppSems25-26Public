

int main() {
    // difference between int[][] and int**
    int** dim2arr = new int*[7];
    for (size_t i = 0; i < 7; ++i) {
        dim2arr[i] = new int[i + 1];
    }

    for (size_t i = 0; i < 7; ++i) {
        delete[] dim2arr[i];
    }
    delete[] dim2arr;

    // !!! 1 dereference vs 2
    // a[i][j] == *(a + i * 5 + j)
    // dim2arr[i][j] = *(*(dim2arr + i) + j);
}
