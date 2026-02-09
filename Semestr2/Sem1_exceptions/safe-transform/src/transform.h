#pragma once

#include <iterator>
#include <vector>

template <typename ForwardIt, typename P, typename F>
void TransformIf(ForwardIt start, ForwardIt finish, P p, F f) {
    using ValueType = typename std::iterator_traits<ForwardIt>::value_type;

    std::vector<ValueType> log;
    log.reserve(std::distance(start, finish));
    for (auto it = start; it != finish; ++it) {
        try {
            log.push_back(*it);
        } catch (...) {
        }

        bool after_predicate = false;
        try {
            if (p(*it)) {
                after_predicate = true;
                f(*it);
            }
        } catch (...) {
            if (after_predicate) {
                ++it;
            }
            for (size_t i = 0; start != it; ++start, ++i) {
                *start = log[i];
            }
            throw;
        }
    }
}
