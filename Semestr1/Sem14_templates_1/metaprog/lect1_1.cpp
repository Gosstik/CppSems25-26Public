// template <int X, typename C>
// class, function, variable, using, consept

template <int X, typename C>
constexpr bool is_size_of = (sizeof(C) == X);
