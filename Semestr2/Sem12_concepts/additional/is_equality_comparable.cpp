#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

template <typename T, typename U, typename = void>
struct is_equality_comparable : std::false_type {};

template <typename T, typename U>
struct is_equality_comparable<
    T,
    U,
    std::void_t<decltype(std::declval<T>() == std::declval<U>())>>
    : std::true_type {};

template <typename T, typename U>
constexpr bool is_equality_comparable_v = is_equality_comparable<T, U>::value;

// NOLINTEND(readability-identifier-naming)

static_assert(is_equality_comparable_v<int, double>);
static_assert(!is_equality_comparable_v<int*, double>);
