#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

////////////////////////////////////////////////////////////////////////////////

//// Simple, but wrong

// template <typename T>
// struct add_lvalue_reference {
//     using type = T&;
// };

// template <>
// struct add_lvalue_reference<void> {
//     using type = void;
// };

////////////////////////////////////////////////////////////////////////////////

//// Sfinae

namespace detail {

template <typename T, typename Enable>
struct add_lvalue_reference_impl {
    using type = T;
};

template <typename T>
struct add_lvalue_reference_impl<T, std::remove_reference_t<T&>> {
    using type = T&;
};

}  // namespace detail

template <typename T>
struct add_lvalue_reference : detail::add_lvalue_reference_impl<T, T> {};

template <typename T>
using add_lvalue_reference_t = add_lvalue_reference<T>::type;

////////////////////////////////////////////////////////////////////////////////

static_assert(std::is_same_v<int&, add_lvalue_reference_t<int>>);
static_assert(std::is_same_v<const int&, add_lvalue_reference_t<const int>>);
static_assert(std::is_same_v<void, add_lvalue_reference_t<void>>);
static_assert(std::is_same_v<const void, add_lvalue_reference_t<const void>>);

// NOLINTEND(readability-identifier-naming)
