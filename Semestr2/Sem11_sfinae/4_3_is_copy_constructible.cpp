#include <type_traits>

// is_copy_constructible

namespace detail {

template <typename T, typename... Args>
std::true_type IsCopyConstructibleImpl(decltype(T(std::declval<T&>()), nullptr));

template <typename...>
std::false_type IsCopyConstructibleImpl(...);

}  // namespace detail

template <typename T>
struct IsCopyConstructible : decltype(detail::IsCopyConstructibleImpl<T>(nullptr)) {};

template <typename T>
const bool is_copy_constructible_v = IsCopyConstructible<T>::value;

////////////////////////////////////////////////////////////////////////////////

struct S {};

struct CopyOnly {
    CopyOnly(const CopyOnly&) = default;
    CopyOnly(CopyOnly&&) noexcept = delete;
};

struct ThrowableMoveOnly {
  ThrowableMoveOnly(const ThrowableMoveOnly&) = delete;
  ThrowableMoveOnly(ThrowableMoveOnly&&) noexcept = default;
};

static_assert(is_copy_constructible_v<S>);
static_assert(is_copy_constructible_v<CopyOnly>);
static_assert(!is_copy_constructible_v<ThrowableMoveOnly>);

int main() {}
