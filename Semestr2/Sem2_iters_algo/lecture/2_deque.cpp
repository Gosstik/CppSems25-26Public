// Two main advantages of std::deque over std::vector:
// 1) insert to front
// 2) pointers are not invalidated in case push_front/back

// Because of 2) std::deque is used by default in container adapters

// Why pop in stack returns void instead of T ???
// To avoid copying in case we just want to remove element

// Insert to deque is O(1) in contrast with vector (amortized O(1)) (cppref).
// Explanation: standard counts only operations over T, reassign of pointers
// is not considered (it is O(n) in case reslocation).
