#include <iterator>
#include <type_traits>

template <typename Tp>
struct MoveIfNoexceptCond : public std::disjunction<
                                std::is_nothrow_move_constructible<Tp>,
                                std::negation<std::is_copy_constructible<Tp>>> {
};

template <typename Tp>  // NOLINTNEXTLINE
constexpr bool move_if_noexcept_cond_v = MoveIfNoexceptCond<Tp>::value;

template <
    typename Iterator,
    typename ReturnType = std::conditional_t<
        move_if_noexcept_cond_v<
            typename std::iterator_traits<Iterator>::value_type>,
        Iterator,
        std::move_iterator<Iterator>>>
constexpr ReturnType MakeMoveIfNoexceptIterator(Iterator iter) {
    return ReturnType(iter);
}
