#include <iostream>
#include <vector>
#include <algorithm>
#include <format>
#include <cmath>
#include <array>
#include <random>

// struct S {
//     int x;
//     int y;
// };

// bool operator<(const S& lhs, const S& rhs) {
//     return lhs.y < rhs.y;
// }

// bool Dist0(const S& lhs, const S& rhs) {
//     return std::abs(lhs.y) < std::abs(rhs.y);
// }

// std::ostream& operator<<(std::ostream& in, const S& val) {
//     in << std::format("({}, {})", val.x, val.y);
//     return in;
// }

template <typename T>
void Print(const std::vector<T>& v) {
    for (const auto& val: v) {
        std::cout << val << ' ';
    }
    // std::cout << '\n';
    std::cout << std::endl;
    // std::cout << std::flush;
}

// template <typename T>
void Lsd(std::vector<uint64_t>& arr) {
    // 2^8

    static const uint64_t cBlockDeg = 8;
    static const uint64_t cBlockSize = 1 << cBlockDeg;
    static const size_t cItersCount = sizeof(uint64_t) / cBlockDeg;

    for (size_t i = 0; i < cItersCount; ++i) {
        // cnt
        std::array<uint64_t, cBlockSize> cnt;
        for (auto val: arr) {
            ++cnt[((val >> (cBlockDeg * i)) & 0b11111111)];
        }

        std::array<uint64_t, cBlockSize + 1> pref;
        pref[0] = 0;
        for (size_t j = 1; j < pref.size(); ++j) {
            pref[j] = pref[j - 1] + cnt[j - 1];
        }

        std::vector<uint64_t> arr2(arr.size());
        for (auto val: arr) {
            arr2[pref[(val >> (cBlockDeg * i) & 0b11111111)]++] = val;
        }
        std::copy(arr2.begin(), arr2.end(), arr.begin());
    }
}

int main() {
    // std::vector<S> v1{{10, 2}, {1, 4}, {1, 1}, {1, -3}, {20, -1}};
    // std::vector<S> v2{{10, 2}, {1, 4}, {1, 1}, {1, -3}, {20, -1}};

    // std::sort(v1.begin(), v1.end());
    // Print(v1);

    // std::sort(v2.begin(), v2.end(), &Dist0);
    // Print(v2);

    std::random_device seeder;
    std::mt19937_64 gen(seeder());
    std::vector<uint64_t> vals;
    for (size_t i = 0; i < 10; ++i) {
        vals.push_back(gen() % 100);
    }
    Lsd(vals);
    for (size_t i = 1; i < vals.size(); ++i) {
        if (vals[i] < vals[i - 1]) {
            std::cout << "FAIL\n";
            Print(vals);
            return 0;
        }
    }
    std::cout << "OK\n";
    Print(vals);
}
