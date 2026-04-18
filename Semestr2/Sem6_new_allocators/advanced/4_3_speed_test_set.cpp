#include <array>
#include <memory_resource>
#include <set>

// monotonic_buffer_resource vs std::allocator
// https://quick-bench.com/q/FBTurrohz3OfgejuluriyxoT3Rw

static void Std(benchmark::State& state) {
    for (auto _ : state) {
        std::set<int> s{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        benchmark::DoNotOptimize(s);
    }
}
// Register the function as a benchmark
BENCHMARK(Std);

static void Pmr(benchmark::State& state) {
    for (auto _ : state) {
        std::array<std::byte, 1024> buffer;
        std::pmr::monotonic_buffer_resource resource(
            buffer.data(), buffer.size());
        std::pmr::set<int> s({1, 2, 3, 4, 5, 6, 7, 8, 9, 10}, &resource);
        benchmark::DoNotOptimize(s);
    }
}
// Register the function as a benchmark
BENCHMARK(Pmr);
