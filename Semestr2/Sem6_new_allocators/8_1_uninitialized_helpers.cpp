#include <memory>

/**
 * Helpers to construct and destroy objects with exceptions handling.
 */
template <typename ForwardIterator, typename Allocator>
void DestroyA(
    ForwardIterator begin, ForwardIterator end, Allocator& allocator) noexcept {
    using AllocTraits = std::allocator_traits<Allocator>;
    for (ForwardIterator cur = begin; cur != end; ++cur) {
        AllocTraits::destroy(allocator, std::addressof(*cur));
    }
}

template <typename ForwardIterator, typename Allocator>
void UninitialisedDefaultA(
    ForwardIterator begin, ForwardIterator end, Allocator& alloc) {
    ForwardIterator cur = begin;
    try {
        using AllocTraits = std::allocator_traits<Allocator>;
        for (; cur != end; ++cur) {
            AllocTraits::construct(alloc, std::addressof(*cur));
        }
    } catch (...) {
        DestroyA(begin, cur, alloc);
        throw;
    }
}

template <typename InputIterator, typename ForwardIterator, typename Allocator>
ForwardIterator UninitializedCopyA(
    InputIterator begin,
    InputIterator end,
    ForwardIterator result,
    Allocator& alloc) {
    ForwardIterator cur = result;
    try {
        using AllocTraits = std::allocator_traits<Allocator>;
        for (; begin != end; ++begin, (void)++cur) {
            AllocTraits::construct(alloc, std::addressof(*cur), *begin);
        }
        return cur;
    } catch (...) {
        DestroyA(result, cur, alloc);
        throw;
    }
}

template <typename InputIterator, typename ForwardIterator, typename Allocator>
ForwardIterator UninitializedMoveA(
    InputIterator begin,
    InputIterator end,
    ForwardIterator result,
    Allocator& alloc) {
    return UninitializedCopyA(
        std::make_move_iterator(begin),
        std::make_move_iterator(end),
        result,
        alloc);
}

template <typename ForwardIterator, typename Tp, typename Allocator>
void UninitializedFillA(
    ForwardIterator first,
    ForwardIterator last,
    const Tp& value,
    Allocator& alloc) {
    ForwardIterator cur = first;
    try {
        using AllocTraits = std::allocator_traits<Allocator>;
        for (; cur != last; ++cur) {
            AllocTraits::construct(alloc, std::addressof(*cur), value);
        }
    } catch (...) {
        DestroyA(first, cur, alloc);
        throw;
    }
}

template <typename Iterator>
struct PairIterator {
    PairIterator(Iterator first, Iterator last) : first(first), last(last) {}
    Iterator first;
    Iterator last;
};

template <
    typename InputIterator1,
    typename InputIterator2,
    typename ForwardIterator,
    typename Allocator>
ForwardIterator UninitializedMoveCopyA(
    PairIterator<InputIterator1> pair1,
    PairIterator<InputIterator2> pair2,
    ForwardIterator result,
    Allocator& alloc) {
    ForwardIterator mid =
        UninitializedMoveA(pair1.first, pair1.last, result, alloc);
    try {
        return UninitializedCopyA(pair2.first, pair2.last, mid, alloc);
    } catch (...) {
        DestroyA(result, mid, alloc);
        throw;
    }
}

template <
    typename InputIterator1,
    typename InputIterator2,
    typename ForwardIterator,
    typename Allocator>
ForwardIterator UninitializedCopyMoveA(
    PairIterator<InputIterator1> pair1,
    PairIterator<InputIterator2> pair2,
    ForwardIterator result,
    Allocator& alloc) {
    ForwardIterator mid =
        UninitializedCopyA(pair1.first, pair1.last, result, alloc);
    try {
        return UninitializedMoveA(pair2.first, pair2.last, mid, alloc);
    } catch (...) {
        DestroyA(result, mid, alloc);
        throw;
    }
}
