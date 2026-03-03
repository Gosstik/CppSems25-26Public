#include <algorithm>
#include <iostream>
#include <iterator>
#include <vector>

// TODO: what if T has no default ctor? (change IstreamIterator ctor)
// probably store optional<T> instead of T

template <typename T>
class IstreamIterator {
  public:
    // NOLINTBEGIN
    using iterator_category = std::input_iterator_tag;
    using pointer = T*;
    using value_type = T;
    using reference = T&;
    using difference_type = std::ptrdiff_t;
    // NOLINTEND

    IstreamIterator() = default;

    IstreamIterator(std::istream& in) : in_(&in) {  // NOLINT
        in >> cur_val_;
    }

    IstreamIterator& operator++() {
        if (in_ == nullptr) {
            return *this;
        }
        if (!(*in_ >> cur_val_)) {
            *this = IstreamIterator();
        }
        return *this;
    }

    // Same operator++(int)

    T& operator*() { return cur_val_; }

    friend bool operator==(
        const IstreamIterator& lhs, const IstreamIterator& rhs) noexcept {
        return lhs.in_ == rhs.in_;
    }

  private:
    // Pointer instead of reference to be able to default initialize
    std::istream* in_ = nullptr;
    T cur_val_;
};

////////////////////////////////////////////////////////////////////////////////

int main() {
    std::istream_iterator<int> it(std::cin);
    std::vector<int> v;

    std::copy(it, std::istream_iterator<int>(), std::back_inserter(v));

    // Print
    for (auto val : v) {
        std::cout << val << ' ';
    }
    std::cout << '\n';
}
