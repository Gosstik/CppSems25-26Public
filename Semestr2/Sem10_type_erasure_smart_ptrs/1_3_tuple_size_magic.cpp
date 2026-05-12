#include <iostream>
#include <tuple>
#include <utility>

// Handy for Deleter in unique_ptr and shared_ptr

struct A {};
struct B {};
struct C {};

static_assert(sizeof(A) == 1);

static_assert(sizeof(std::pair<A, B>) == 2);
static_assert(sizeof(std::pair<A*, B>) == 16);

static_assert(sizeof(std::tuple<A, B>) == 1);
static_assert(sizeof(std::tuple<A*, B>) == 8);

static_assert(sizeof(std::tuple<A*, B, C>) == 8);

int main() {}
