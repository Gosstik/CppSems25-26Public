#include <type_traits>
#include <vector>

// NOLINTBEGIN(readability-identifier-naming)

// !!! Try to avoid using that, use void_t instead

namespace detail {

template <typename T>
std::true_type has_size_type_impl(decltype(typename T::size_type{}, nullptr));

//// same effect as above
// template <typename T>
// auto HasSizeTypeImpl(void*) -> decltype(typename T::size_type{},
// std::true_type{});

template <typename...>  // ! Must be template
std::false_type has_size_type_impl(...);

}  // namespace detail

template <typename T>
struct HasSizeType : decltype(detail::has_size_type_impl<T>(nullptr)) {};

template <typename T>
constexpr bool has_size_type_v = HasSizeType<T>::value;

////////////////////////////////////////////////////////////////////////////////

static_assert(!has_size_type_v<int>);
static_assert(has_size_type_v<std::vector<int>>);

int main() {}

// NOLINTEND(readability-identifier-naming)
