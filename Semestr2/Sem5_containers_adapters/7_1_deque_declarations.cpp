#pragma once

#include <cstddef>
#include <iterator>

template <typename T>
class Deque {
  private:
    template <bool IsConst>
    struct iterator_impl {
        using value_type = T;
        using pointer = T*;  // FIX
        using reference = T&;
        using difference_type = ptrdiff_t;
        using iterator_category = std::random_access_iterator_tag;

        iterator_impl();
        iterator_impl(const iterator_impl& other) = default;
        iterator_impl& operator=(const iterator_impl& other) = default;
        ~iterator_impl() = default;

        operator iterator_impl<true>() const;

        iterator_impl& operator++();
        iterator_impl operator++(int);

        iterator_impl& operator--();
        iterator_impl operator--(int);

        iterator_impl operator+(difference_type diff);
        iterator_impl operator-(difference_type diff);

        value_type& operator*();
        pointer operator->();

        // TODO: cast const to non-const

        // NOTE: we cannot declare compare operators inside iterator
        // because we must compare const/non-const iterators
    };

  public:
    using value_type = T;
    using size_type = size_t;
    using difference_type = typename iterator_impl<true>::difference_type;
    using reference = T&;
    using const_reference = const T&;
    using pointer = T*;
    using const_pointer = const T*;
    using iterator = iterator_impl<false>;
    using const_iterator = iterator_impl<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    Deque();
    Deque(const Deque& other);
    explicit Deque(int sz, const T& = T());
    Deque& operator=(const Deque& other);
    ~Deque();

    size_t size() const noexcept;

    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;

    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;

    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    T& operator[](size_t index);
    const T& operator[](size_t index) const;

    T& at(size_t i);
    const T& at(size_t i) const;

    void push_back(const T& val);
    void pop_back();
    void push_front(const T& val);
    void pop_front();

    iterator insert(const_iterator pos, const T& val);
    iterator erase(const_iterator pos);
};

template <typename T>
Deque<T>::iterator operator+(
    typename Deque<T>::iterator::difference_type diff,
    const typename Deque<T>::const_iterator& it);

template <typename T>
Deque<T>::iterator operator-(
    typename Deque<T>::iterator::difference_type diff,
    const typename Deque<T>::const_iterator& it);

template <typename T>
Deque<T>::iterator operator-(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);

template <typename T>
Deque<T>::iterator operator<(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);

template <typename T>
Deque<T>::iterator operator==(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);

template <typename T>
Deque<T>::iterator operator>(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);

template <typename T>
Deque<T>::iterator operator<=(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);

template <typename T>
Deque<T>::iterator operator>=(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);

template <typename T>
Deque<T>::iterator operator!=(
    const typename Deque<T>::const_iterator& lhs,
    const typename Deque<T>::const_iterator& rhs);
