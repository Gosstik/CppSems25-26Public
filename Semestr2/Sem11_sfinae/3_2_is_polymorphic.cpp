#include <type_traits>

// https://en.cppreference.com/w/cpp/types/is_polymorphic

namespace detail {

template <class T>
std::true_type IsPolymorphicImpl(
    decltype(dynamic_cast<const volatile void*>(static_cast<T*>(nullptr))));
template <class T>
std::false_type IsPolymorphicImpl(...);

}  // namespace detail

template <class T>
struct IsPolymorphic : decltype(detail::IsPolymorphicImpl<T>(nullptr)) {};

template <class T>
constexpr bool is_polymorphic_v = IsPolymorphic<T>::value;

////////////////////////////////////////////////////////////////////////////////

struct Poly {
    virtual ~Poly() = default;
};

static_assert(is_polymorphic_v<Poly>);
static_assert(!is_polymorphic_v<int>);
static_assert(!is_polymorphic_v<std::true_type>);

// static_assert(is_polymorphic_v<void>);  // Why CE ???

struct Base {};

struct Derived : Base {};

int main() {
    // dynamic_cast<void*>(static_cast<void*>(nullptr)); // CE
    Base* b;
    Derived* d;
    // b = static_cast<Base*>(d); // OK
    // b(d);
    // d = dynamic_cast<Derived*>(b); // CE
}
