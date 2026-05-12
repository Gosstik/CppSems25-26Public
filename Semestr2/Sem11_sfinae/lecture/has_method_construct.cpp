#include <type_traits>

// For allocator_traits::construct

namespace detail {

//// does not work when returning int&, so use comma trick
// template <typename T, typename... Args>
// std::true_type test( decltype(T().construct(Args()...))* );

template <typename T, typename... Args>
std::true_type HasMethodConstructImpl(
    decltype(std::declval<T>().construct(std::declval<Args>()...), nullptr));

template <typename...>  // without it does not work
std::false_type HasMethodConstructImpl(...);

}  // namespace detail

template <typename T, typename... Args>
struct HasMethodConstruct
    : decltype(detail::HasMethodConstructImpl<T, Args...>(nullptr)) {};

template <typename T, typename... Args>
const bool has_method_construct_v = HasMethodConstruct<T, Args...>::value;

////////////////////////////////////////////////////////////////////////////////

// NOLINTBEGIN(readability-identifier-naming)

struct S {
    void construct(int, int);
};

struct NoDefaultCtor {
    NoDefaultCtor(int) {}  // NOLINT
    void construct(bool);
};

struct ConstructReturnsRef {
    int& construct(bool);
};

struct A;  // incomplete type

struct RefA {
    void construct(A&);
};

struct JustA {
    void construct(A a);  // false negative
    // void construct(A&&); // works fine T&& in decltype helps to solve this
};

// NOLINTEND(readability-identifier-naming)

static_assert(has_method_construct_v<S, int, int>);
static_assert(!has_method_construct_v<S, int>);

static_assert(has_method_construct_v<NoDefaultCtor, bool>);
static_assert(!has_method_construct_v<NoDefaultCtor, void>);

static_assert(has_method_construct_v<ConstructReturnsRef, bool>);
static_assert(!has_method_construct_v<ConstructReturnsRef, void>);

// static_assert(has_method_construct_v<JustA, A>); // CE
static_assert(!has_method_construct_v<RefA, A>);

int main() {}
