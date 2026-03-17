#include <cstdint>
#include <iostream>
#include <ranges>

class FibonacciView : public std::ranges::view_interface<FibonacciView> {
  public:
    class iterator {
      public:
        using value_type = std::uint64_t;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;

        value_type operator*() const { return a_; }

        iterator& operator++() {
            auto next = a_ + b_;
            a_ = b_;
            b_ = next;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        // Infinite range - iterators are equal only if both at same position
        bool operator==(const iterator& other) const {
            return a_ == other.a_ && b_ == other.b_;
        }

      private:
        value_type a_ = 0, b_ = 1;
    };

    iterator begin() const { return {}; }
    // !!! NOTE
    std::unreachable_sentinel_t end() const { return {}; }
};

// Some magic
template <>
inline constexpr bool std::ranges::enable_view<FibonacciView> = true;

int main() {
    // FibonacciView fibonacci;

    // ??? use fibonacci instead of FibonacciView()
    auto even_fibs = FibonacciView()
                | std::views::filter([](auto n) { return n % 2 == 0; })
                | std::views::take(8);

    for (auto n : even_fibs) {
        std::cout << n << ' ';
    }

    for (auto n : even_fibs) {
        std::cout << n << ' ';
    }
}
