#include <ranges>
#include <iostream>
#include <cstdint>

class FibonacciView : public std::ranges::view_interface<FibonacciView> {
public:
    class iterator {
    public:
        using value_type = std::uint64_t;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::input_iterator_tag;

        iterator() = default;
        explicit iterator(int count) : remaining_(count) {}

        value_type operator*() const { return a_; }

        iterator& operator++() {
            auto next = a_ + b_;
            a_ = b_;
            b_ = next;
            --remaining_;
            return *this;
        }

        iterator operator++(int) {
            auto tmp = *this;
            ++(*this);
            return tmp;
        }

        bool operator==(const iterator& other) const {
            return remaining_ == other.remaining_;
        }

    private:
        value_type a_ = 0, b_ = 1;
        int remaining_ = 0;
    };

    FibonacciView() = default;
    explicit FibonacciView(int count) : count_(count) {}

    iterator begin() const { return iterator(count_); }
    iterator end() const { return iterator(0); }

private:
    int count_ = 0;
};

// Some magic
template<>
inline constexpr bool std::ranges::enable_view<FibonacciView> = true;

int main() {
    auto even_fibs = FibonacciView(20)
                   | std::views::filter([](auto n) { return n % 2 == 0; })
                   | std::views::take(5);

    for (auto n : even_fibs) {
        std::cout << n << ' ';
    }
}
