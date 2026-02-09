#include <iostream>

/// O(n)

namespace detail {

template <int N, int D>
struct IsPrimeImpl {
    static constexpr bool value =
        N % D == 0 ? false : IsPrimeImpl<N, D - 1>::value;
};

template <int N>
struct IsPrimeImpl<N, 1> {
    static constexpr bool value = true;
};

}  // namespace detail

template <int N>
struct IsPrime {
    static constexpr bool value = detail::IsPrimeImpl<N, N - 1>::value;
};

template <>
struct IsPrime<1> {
    static constexpr bool value = false;
};

template <int N>
const bool is_prime_v = IsPrime<N>::value;

////////////////////////////////////////////////////////////////////////////////

/// O(sqrt(N))

namespace detail {

template <int N, int D, bool>
struct IsPrimeFastImpl {
  private:
    static constexpr int D1 = D + 1;  // NOLINT

  public:
    static constexpr bool value =
        (N % D == 0) ? false : IsPrimeFastImpl<N, D1, (N < D1 * D1)>::value;
};

template <int N, int D>
struct IsPrimeFastImpl<N, D, true> {
    static constexpr bool value = true;
};

template <int D>
struct IsPrimeFastImpl<1, D, true> {
    static constexpr bool value = false;
};

}  // namespace detail

template <int N>
struct IsPrimeFast {
    static constexpr bool value = detail::IsPrimeFastImpl<N, 2, false>::value;
};

template <int N>
constexpr bool is_prime_fast_v = IsPrimeFast<N>::value;

////////////////////////////////////////////////////////////////////////////////

static_assert(!is_prime_fast_v<1>);
static_assert(!is_prime_fast_v<2>);
static_assert(is_prime_fast_v<3>);
static_assert(!is_prime_fast_v<4>);
static_assert(is_prime_fast_v<5>);
static_assert(!is_prime_fast_v<6>);
static_assert(is_prime_fast_v<7>);
static_assert(!is_prime_fast_v<8>);
static_assert(!is_prime_fast_v<9>);
static_assert(!is_prime_fast_v<256>);
static_assert(is_prime_fast_v<257>);
static_assert(is_prime_fast_v<1'000'003>);  // Check recursion limit

////////////////////////////////////////////////////////////////////////////////

void TestIsPrime() {
    std::cout << IsPrime<257>::value;
    std::cout << is_prime_v<257> << '\n';
    static_assert(is_prime_v<257>);
}
