#include <iostream>
#include <vector>
#include <random>
#include <chrono>

std::vector<uint64_t> g;

const uint64_t kItersCount = 10;

void Slow(std::vector<uint64_t> v) {
    g.push_back(v.back());
    if (g.size() >= 100) {
        g.clear();
    }
}

void Fast(std::vector<uint64_t>* v) {
    g.push_back(v->back());
    if (g.size() >= 100) {
        g.clear();
    }
}

int main() {
    // Init
    std::cout << "Initializing vector\n";
    std::vector<uint64_t> v;
    uint64_t div = std::random_device{}();
    for (uint64_t i = 0; i < 10'000'000; ++i) {
        v.push_back(i % div);
    }

    using TimePoint = std::chrono::high_resolution_clock::time_point;

    std::cout << "Start bench\n";

    // Slow
    {
        TimePoint start = std::chrono::high_resolution_clock::now();
        for (uint64_t i = 0; i < kItersCount; ++i) {
            Slow(v);
        }
        TimePoint end = std::chrono::high_resolution_clock::now();
        std::cout << "Slow ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }

    // Fast
    {
        TimePoint start = std::chrono::high_resolution_clock::now();
        for (uint64_t i = 0; i < kItersCount; ++i) {
            Fast(&v);
        }
        TimePoint end = std::chrono::high_resolution_clock::now();
        std::cout << "Fast ms: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << std::endl;
    }
}
