#include <type_traits>

// std::move_if_noexcept
// https://en.cppreference.com/w/cpp/utility/move_if_noexcept.html

template <typename Tp>
struct MoveIfNoexceptCond : public std::disjunction<
                                std::is_nothrow_move_constructible<Tp>,
                                std::negation<std::is_copy_constructible<Tp>>> {
};

template <typename Tp>  // NOLINTNEXTLINE
constexpr bool move_if_noexcept_cond_v = MoveIfNoexceptCond<Tp>::value;
