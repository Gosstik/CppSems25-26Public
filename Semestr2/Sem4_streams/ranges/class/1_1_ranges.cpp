// Main idea of std::ranges library:
// Arbitrary range is not always a pair of iterator.
// In most cases end() iterator is singular (uninitialized).
// So, define range as a pair of iterators is not a goo idea.
// Solution in std::ranges: range is iterator + sentinel (guard, limiter)

// Example: std::istream_iterator

// Metaproga: https://vkvideo.ru/playlist/-206078025_85/video-206078025_456239947

// C-strings, streams, endless sequence

// ranges::begin(cont)
// ranges::end(cont)

// iterator_t
// range: begin + end
// sentinel_for
