#include <type_traits>

// shrink_to_fit must have strong exception safery
// if type is only move constructible, it must be noexcept, otherwise
// shrink_to_fit will do nothing

template <
    typename Container,
    bool = std::disjunction_v<
        std::is_copy_constructible<typename Container::value_type>,
        std::is_nothrow_move_constructible<typename Container::value_type>>>
struct ShrinkToFitAux {
    static bool do_it(Container& /*unused*/) noexcept { return false; }
};

template <typename Container>
struct ShrinkToFitAux<Container, true> {
    static bool do_it(Container& container) noexcept {
        try {
            Container(
                MakeMoveIfNoexceptIterator(container.begin()),
                MakeMoveIfNoexceptIterator(container.end()),
                container.get_allocator())
                .swap(container);
        } catch (...) {
            return false;
        }
    }
};
