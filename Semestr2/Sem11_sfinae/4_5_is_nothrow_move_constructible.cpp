#include <type_traits>

namespace detail {

//// Option 1 (enable_if)
template <typename T, typename... Args>
std::true_type IsNothrowMoveConstructibleImpl(
    std::enable_if_t<noexcept(T(std::declval<T&&>())), decltype(nullptr)>);

//// Option 2 (trailing return type)
// template <typename T, typename... Args>
// auto IsNothrowMoveConstructibleImpl(void*)
//     -> std::bool_constant<noexcept(T(std::declval<T&&>()))>;

template <typename...>
std::false_type IsNothrowMoveConstructibleImpl(...);

}  // namespace detail

template <typename T>
struct IsNothrowMoveConstructible
    : decltype(detail::IsNothrowMoveConstructibleImpl<T>(nullptr)) {};

template <typename T>
const bool is_nothrow_move_constructible_v =
    IsNothrowMoveConstructible<T>::value;

////////////////////////////////////////////////////////////////////////////////

struct S {};

struct CopyOnly {
    CopyOnly(const CopyOnly&) = default;
    CopyOnly(CopyOnly&&) noexcept = delete;
};

struct ThrowableMoveOnly {
    ThrowableMoveOnly(const ThrowableMoveOnly&) = delete;
    // noexcept by default, must be explicitly specified noexcept(false)
    ThrowableMoveOnly(ThrowableMoveOnly&&) noexcept(false) = default;
};

struct NoexceptMoveOnly {
    NoexceptMoveOnly(NoexceptMoveOnly&) = delete;
    NoexceptMoveOnly(NoexceptMoveOnly&&) noexcept = default;
};

static_assert(is_nothrow_move_constructible_v<S>);
static_assert(!is_nothrow_move_constructible_v<CopyOnly>);
static_assert(is_nothrow_move_constructible_v<NoexceptMoveOnly>);
static_assert(!is_nothrow_move_constructible_v<ThrowableMoveOnly>);

// struct My {
//   My(My&&) = delete;
// };

// #include <iostream>

// template <typename T>
// constexpr bool my_is_noexcept = noexcept(T(std::declval<T&&>()));

// int main() {
//   // const bool is_noexcept = my_is_noexcept<My>;
//   const bool is_noexcept = my_is_noexcept<My>;
//   std::cout << is_noexcept << '\n';
// }
