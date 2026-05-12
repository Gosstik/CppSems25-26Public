#include <type_traits>

// NOLINTBEGIN(readability-identifier-naming)

//// Version for public inheritance

namespace detail {

template <typename B, typename D>
std::true_type test_is_base_of_public(const volatile B*);

template <typename...>
std::false_type test_is_base_of_public(...);

}  // namespace detail

template <typename B, typename D>
struct is_base_of_public
    : std::conjunction<
          std::is_class<B>,  // !!! meta class, not _t versions
          std::is_class<D>,
          decltype(detail::test_is_base_of_public<B, D>(
              static_cast<D*>(nullptr)))> {};

template <typename B, typename D>
constexpr bool is_base_of_public_v = is_base_of_public<B, D>::value;

////////////////////////////////////////////////////////////////////////////////

//// Correct version (takes into account private and ambiguous base)

// https://en.cppreference.com/w/cpp/types/is_base_of

namespace details {

template <typename B>
std::true_type test_ptr_conv(const volatile B*);
template <typename>
std::false_type test_ptr_conv(const volatile void*);

template <typename B, typename D>
auto test_is_base_of(int)
    -> decltype(test_ptr_conv<B>(static_cast<D*>(nullptr)));
template <typename, typename>
auto test_is_base_of(...) -> std::true_type;  // private or ambiguous base

}  // namespace details

template <typename Base, typename Derived>
struct is_base_of
    : std::integral_constant<
          bool,
          std::is_class<Base>::value &&
              std::is_class<Derived>::
                  value&& decltype(details::test_is_base_of<Base, Derived>(
                      0))::value> {};

template <typename B, typename D>
constexpr bool is_base_of_v = is_base_of<B, D>::value;

////////////////////////////////////////////////////////////////////////////////

// NOLINTEND(readability-identifier-naming)

struct Base {};
struct PublicParent : public Base {};
struct PrivateParent : private Base {};

static_assert(is_base_of_public_v<Base, PublicParent>);
static_assert(!is_base_of_public_v<PublicParent, Base>);

static_assert(is_base_of_v<Base, PublicParent>);
static_assert(is_base_of_v<Base, PrivateParent>);
static_assert(!is_base_of_v<PublicParent, Base>);

int main() {}
