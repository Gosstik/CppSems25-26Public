template <typename It>
concept InputIterator = requires(It x, It y) {
    *x;
    ++y;
    x != y;
};

template <typename It>
concept ForwardIterator = InputIterator<It> && requires(It it) { it++; };

template <typename It>
concept BidirectionalIterator = ForwardIterator<It> && requires(It it) {
    --it;
    it--;
};

// clang-format off

template <typename It>
concept RandomAccessIterator =
    BidirectionalIterator<It> && requires(It x, It y) {
      x + 1; x - 1; 1 + x;
      x += 1; x -= 1;
      x - y;
      x < y; x > y; x <= y; x >= y;
    };

// clang-format on
