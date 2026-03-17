#include <cstddef>
#include <mdspan>
#include <vector>
#include <iostream>

// mdspan (C++23)
// https://en.cppreference.com/w/cpp/container/mdspan

// template<
//     class T,
//     class Extents,
//     class LayoutPolicy = std::layout_right,
//     class AccessorPolicy = std::default_accessor<T>
// > class mdspan;

int main() {
    std::vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

    // View data as contiguous memory representing 2 rows of 6 ints each
    auto ms2 = std::mdspan<int>(v.data(), 2, 6);
    // View the same data as a 3D array 2 x 3 x 2
    auto ms3 = std::mdspan(v.data(), 4, 3, 2);

    // Write data using 2D view
    for (size_t i = 0; i != ms2.extent(0); ++i) {
        for (size_t j = 0; j != ms2.extent(1); ++j) {
            ms2[i, j] = i * 1000 + j;
        }
    }

    // Read back using 3D view
    for (size_t i = 0; i != ms3.extent(0); i++) {
        std::cout << "slice @ i = " << i << '\n';
        for (std::size_t j = 0; j != ms3.extent(1); j++) {
            for (std::size_t k = 0; k != ms3.extent(2); k++) {
                std::cout << ms3[i, j, k] << " ";
            }
            std::cout << "\n";
        }
    }
}
