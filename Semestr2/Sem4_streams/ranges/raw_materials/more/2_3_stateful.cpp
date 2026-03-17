// Why std::for_each return UnaryFunc, but std::sort returns void (instead of
// Comp) ? --- UnaryFunc may be stateful (as accumulate), but comparator in
// sort cannot be.
