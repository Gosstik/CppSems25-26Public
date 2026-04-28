#include <cstddef>
#include <iostream>
#include <type_traits>

// Why reverse:
// https://stackoverflow.com/questions/27663641/why-does-libstdc-store-stdtuple-elements-in-reverse-order
// Why forward:
// https://stackoverflow.com/questions/9641699/why-is-it-not-good-to-use-recursive-inheritance-for-stdtuple-implementations/9643480#9643480

// libc impl:
// https://github.com/llvm/llvm-project/blob/main/libcxx/include/tuple

////////////////////////////////////////////////////////////////////////////////
//// TupleLeaf

template <size_t Index, typename T>
class TupleLeaf {
  public:
    TupleLeaf& operator=(const TupleLeaf&) = delete;

    TupleLeaf() noexcept(std::is_nothrow_default_constructible_v<T>) : value() {
        static_assert(
            !std::is_reference_v<T>,
            "Attempted to default construct a reference element in a tuple");
    }

  private:
    T value;
};

////////////////////////////////////////////////////////////////////////////////
//// Tuple

template <typename... Ts>
class Tuple {};

// template <typename Head, typename... Tail>
// class Tuple<Head, Tail...> {
//   Head h;
//   Tuple<Tail...> t;
// };

// template <typename Head, typename... Tail>
// class Tuple<Head, Tail...>: Tuple<Tail...>, LeafImpl<Head> {
//   // Head h;
// };

template <typename... Tail>
class Tuple<Tail...> : public TupleLeaf<, Tail...> {}
