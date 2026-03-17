#include <deque>

// NOTE: instead of IsConst in template parameters sometimes use only types:
// template <typename Tp, typename Ref, typename Ptr>
// class DequeIterator { ... }

////////////////////////////////////////////////////////////////////////////////

template <typename Tp, bool IsConst>
struct DequeIterator {
    // !!! private
  private:
    using self = DequeIterator;  // Convenient short alias.
    using iterator = DequeIterator<Tp, false>;
    using const_iterator = DequeIterator<Tp, true>;

    template <typename Tp1, typename Alloc1>
    friend class Deque;

    template <typename Tp1, typename Alloc1>
    friend class DequeBase;
};

////////////////////////////////////////////////////////////////////////////////

int main() {
    std::deque<int> d;
    d.push_back(1);
}
