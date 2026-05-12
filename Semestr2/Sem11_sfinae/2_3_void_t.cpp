#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

template <typename...>
using void_t = void;

////////////////////////////////////////////////////////////////////////////////

//// add_lvalue_reference

namespace detail {

template <typename T, typename Enable>
struct add_lvalue_reference_impl {
    using type = T;
};

template <typename T>
struct add_lvalue_reference_impl<T, std::void_t<T&>> {
    using type = T&;
};

}  // namespace detail

template <typename T>
struct add_lvalue_reference : detail::add_lvalue_reference_impl<T, void> {};

template <typename T>
using add_lvalue_reference_t = add_lvalue_reference<T>::type;

//// Tests

static_assert(std::is_same_v<int&, add_lvalue_reference_t<int>>);
static_assert(std::is_same_v<const int&, add_lvalue_reference_t<const int>>);
static_assert(std::is_same_v<void, add_lvalue_reference_t<void>>);
static_assert(std::is_same_v<const void, add_lvalue_reference_t<const void>>);

////////////////////////////////////////////////////////////////////////////////

//// has_inner_type

template <typename T, typename = void>
struct has_inner_type : std::false_type {};

template <typename T>
struct has_inner_type<T, std::void_t<typename T::Inner>> : std::true_type {};

template <typename T>
constexpr bool has_inner_type_v = has_inner_type<T>::value;

//// Tests

struct A {
    using Inner = int;
};

struct B {
    struct Inner {};
};

struct C {
    struct Outer {};
};

static_assert(has_inner_type_v<A>);
static_assert(has_inner_type_v<B>);
static_assert(!has_inner_type_v<C>);

////////////////////////////////////////////////////////////////////////////////

// NOLINTEND(readability-identifier-naming)
