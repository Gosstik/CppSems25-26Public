#include <iostream>
#include <random>
#include <vector>

// BinSearch searched for x in [left, right)
int BinSearch(const std::vector<int>& arr, int x, int left, int right) {
    if (right - left == 1) {
        if (x == arr[left]) {
            return left;
        }
        return -1;
    }

    int mid = (left + right) / 2;

    if (x < arr[mid]) {
        return BinSearch(arr, x, mid, right);
    }
    return BinSearch(arr, x, left, mid);
}

int LinearSearch(const std::vector<int>& arr, int x, int n) {
    for (int i = n - 1; i >= 0; i--) {
        if (arr[i] == x) {
            return i;
        }
    }
    return -1;
}

void Solve() {
    int n{};
    int x{};
    std::cin >> n >> x;

    // Array is sorted in non-decreasing order
    std::vector<int> array(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> array[i];
    }

    std::cout << BinSearch(array, x, 0, n);
}

void PrintInput(const std::vector<int>& arr, int x, int n) {
    std::cout << n << ' ' << x << '\n';
    for (int i = 0; i < n; i++) {
        std::cout << arr[i] << ' ';
    }
}

bool StressTest() {
    const int kItersCount = 1000;
    const int kMaxLength = 1000000;
    const int kMaxDelta = 1000;

    std::mt19937_64 gen(std::random_device{}());

    for (int iter = 0; iter < kItersCount; iter++) {
        // int arr_len = std::rand() % kMaxLength + 1;
        int n = static_cast<int>(gen()) % kMaxLength + 1;
        std::vector<int> arr(n);

        arr[0] = static_cast<int>(gen()) % kMaxDelta;
        for (int i = 1; i < n; i++) {
            arr[i] = arr[i - 1] + static_cast<int>(gen()) % kMaxDelta;
        }

        int x = arr[static_cast<int>(gen()) % n];
        if (BinSearch(arr, x, 0, n) != LinearSearch(arr, x, n)) {
            PrintInput(arr, x, n);
            return false;
        }

        x = static_cast<int>(gen());
        if (BinSearch(arr, x, 0, n) != LinearSearch(arr, x, n)) {
            PrintInput(arr, x, n);
            return false;
        }
    }

    return true;
}

int main() { Solve(); }
