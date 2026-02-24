#include <cstddef>
#include <iterator>
#include <type_traits>
#include <vector>

// Example of minimum ForwardIterator:
// https://en.cppreference.com/w/cpp/iterator/forward_iterator.html

// operator->
// const methods and const iterators
// cast non-const to const
// reverse_iterator

// ! In vector iterator = T*.

template <typename T>
class Vector {
  private:
    template <bool IsConst>
    class IteratorImpl {
      public:
        // NOLINTBEGIN
        using iterator_category = std::random_access_iterator_tag;
        using value_type = T;
        using reference = std::conditional_t<IsConst, const T&, T&>;
        using pointer = std::conditional_t<IsConst, const T*, T*>;
        using difference_type = std::ptrdiff_t;
        // NOLINTEND

        IteratorImpl(const IteratorImpl&) = default;
        IteratorImpl& operator=(const IteratorImpl&) = default;

        reference operator*() const {  // SAME FOR CONST AND NON CONST METHODS
            return *cur_;
        }

        pointer operator->() const { return cur_; }

        IteratorImpl& operator++() {
            ++cur_;
            return *this;
        }

        IteratorImpl operator++(int) {
            IteratorImpl res(*this);
            ++cur_;
            return res;
        }

        // Cast
        operator IteratorImpl<true>() {  // NOLINT(google-explicit-constructor)
            return {cur_};
        }

      private:
        IteratorImpl(pointer ptr)  // NOLINT(google-explicit-constructor)
            : cur_(ptr) {}

        // Template friends
        // https://en.cppreference.com/w/cpp/language/friend
        friend class Vector<T>;

        pointer cur_;
    };

  public:
    // NOLINTBEGIN
    using iterator = IteratorImpl<false>;
    using const_iterator = IteratorImpl<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() { return {arr_}; }

    iterator end() { return {arr_ + size_}; }

    const_iterator begin() const { return {arr_}; }

    const_iterator end() const { return {arr_ + size_}; }

    const_iterator cbegin() const { return {arr_}; }

    const_iterator cend() const { return {arr_ + size_}; }

    // Same with reverse versions

    // NOLINTEND

  private:
    T* arr_;
    size_t size_;
    size_t cap_;
};

////////////////////////////////////////////

int main() {
    typename std::vector<int>::iterator it{}; // T*
    const typename std::vector<int>::iterator cit{}; // T* const
    typename std::vector<int>::const_iterator ccit{}; // const T*
    const typename std::vector<int>::const_iterator cccit{}; // const T* const
}
