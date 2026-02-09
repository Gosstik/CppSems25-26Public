#include <cstdint>

// Will compile?

template <uint64_t N>
constexpr uint64_t fib = (N < 2) ? 1 : fib<N-1> + fib<N-2>;

static_assert(fib<49> == 12586269025ULL);

//////////////////////

template <uint64_t N>
constexpr uint64_t fib2 = fib<N-1> + fib<N-2>;

template <>
constexpr uint64_t fib2<0> = 1;

template <>
constexpr uint64_t fib2<1> = 1;

static_assert(fib2<49> == 12586269025ULL);

//////////////////////

// specializations for true and false type

