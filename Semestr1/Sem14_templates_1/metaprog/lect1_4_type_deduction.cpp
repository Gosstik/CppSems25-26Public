template <typename T>
T abs(T);

auto a = abs(-.4f);
auto b = abs(32u);

////////////////

// Will compile?

template <typename T, typename U>
T id(U val) {
  return val;
}

auto c = id(14ll);
