#include <flat_set>
#include <iostream>

// std::flat_set (C+23)
// https://en.cppreference.com/w/cpp/container/flat_set.html

// !!! The complexity of insertion and erasure operations is linear
// !!! It is container adaptor, not a view

// template<
//     class Key,
//     class Compare = std::less<Key>,
//     class KeyContainer = std::vector<Key> // array, deque
// > class flat_set;

// Contiguous location in memory means better cache performance than std::set.
// Supported operations that are not present in std::vector:
// - insert   - O(n)
// - erase    - O(n)
// - contains - O(log(n))
// - find     - O(log(n))

int main() {
    std::flat_set<int> fs{5, 2, 8, 1, 9, 3};

    // Elements are automatically sorted
    for (int x : fs) {
        std::cout << x << " ";  // Output: 1 2 3 5 8 9
    }
    std::cout << "\n";

    // Insert elements
    fs.insert(4);
    fs.insert(2);  // Duplicate - ignored

    // Check if element exists
    if (fs.contains(5)) {
        std::cout << "Found 5\n";
    }

    // Find element
    auto it = fs.find(3);
    if (it != fs.end()) {
        std::cout << "Found: " << *it << "\n";
    }

    // Erase element
    fs.erase(8);

    // Size
    std::cout << "Size: " << fs.size() << "\n";
}
