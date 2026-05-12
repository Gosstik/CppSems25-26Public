#include <type_traits>

template <typename From, typename To>
concept convertible_to = std::is_convertible_v<From, To> &&
                         requires(From (&f)()) { static_cast<To>(f()); };
