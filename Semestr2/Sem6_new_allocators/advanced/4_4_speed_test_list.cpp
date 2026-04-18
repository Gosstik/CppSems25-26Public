#include <array>
#include <list>
#include <memory_resource>

// monotonic_buffer_resource vs std::allocator
// https://quick-bench.com/q/6Vdv-MRBaCcEWB8H1yxU6hlUr3o

static void Std(benchmark::State& state) {
    for (auto _ : state) {
        std::list<int> l;
        for (int i = 0; i < 100; ++i) {
            l.push_back(i);
        }
        benchmark::DoNotOptimize(l);
    }
}
// Register the function as a benchmark
BENCHMARK(Std);

static void Pmr(benchmark::State& state) {
    for (auto _ : state) {
        std::array<std::byte, 1024> buffer;
        std::pmr::monotonic_buffer_resource resource(
            buffer.data(), buffer.size());
        std::pmr::list<int> l(&resource);
        for (int i = 0; i < 100; ++i) {
            l.push_back(i);
        }
        benchmark::DoNotOptimize(l);
    }
}
// Register the function as a benchmark
BENCHMARK(Pmr);
