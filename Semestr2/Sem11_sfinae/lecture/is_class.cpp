#include <type_traits>

// Impl with std::is_union:
// https://en.cppreference.com/w/cpp/types/is_class

namespace detail {

template <class T>
std::true_type IsClassImpl(int T::*);

template <class>
std::false_type IsClassImpl(...);

}  // namespace detail

template <class T>
struct IsClass : decltype(detail::IsClassImpl<T>(nullptr)) {};

template <class T>
constexpr bool is_class_v = IsClass<T>::value;

////////////////////////////////////////////////////////////////////////////////

static_assert(!is_class_v<int>);
static_assert(is_class_v<std::true_type>);
