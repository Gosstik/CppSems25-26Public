#include <algorithm>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <memory>
#include <type_traits>
#include <vector>

struct S {
    // S() = default;
    S(int x) : x(x) {}

    int x = 1;
    int* y = nullptr;
};

template <typename T>
class Vector {
  public:
    Vector() = default;

    void Reserve(size_t new_cap) {
        T* new_arr = reinterpret_cast<T*>(new char[new_cap * sizeof(T)]);
        // T* new_arr = new T[new_cap];

        size_t last = 0;

        try {
            std::uninitialized_copy(arr_, arr_ + size_, new_arr);
        } catch (...) {
            delete[] reinterpret_cast<char*>(new_arr);
            throw;
        }

        for (size_t i = 0; i < size_; ++i) {
            arr_[i].~T();
        }

        delete[] reinterpret_cast<char*>(arr_);
        arr_ = new_arr;
        cap_ = new_cap;
    }

    void PushBack(const T& val) {
        if (size_ == cap_) {
            Reserve(cap_ == 0 ? 1 : 2 * cap_);
        }
        arr_[size_++] = val;
        // push last elem
    }

    template <bool IsConst>
    struct Iterator {
        Iterator() = default;
        Iterator(const Iterator<IsConst>& other) = default;
        Iterator& operator=(const Iterator& other) = default;
        ~Iterator() = default;

        using value_type = T;
        using reference = std::conditional_t<IsConst, const T, T>&;
        using pointer = std::conditional_t<IsConst, const T, T>*;
        using iterator_category = std::random_access_iterator_tag;
        using difference_type = std::ptrdiff_t;

        operator Iterator<true>() const { return {ptr_}; }

        reference operator*() const { return *ptr_; }

        pointer operator->() const { return ptr_; }

        reference operator[](difference_type n) const { return ptr_[n]; }

        Iterator& operator++() {
            ++ptr_;
            return *this;
        }

        Iterator operator++(int) {
            Iterator copy = *this;
            ++(*this);
            return copy;
        }

        Iterator& operator--() {
            --ptr_;
            return *this;
        }

        Iterator operator--(int) {
            Iterator copy = *this;
            --(*this);
            return copy;
        }

        Iterator operator+(difference_type n) const {
            return Iterator{ptr_ + n};
        }

        friend Iterator operator+(difference_type n, Iterator other) {
            return other + n;
        }

        Iterator operator-(difference_type n) const {
            return Iterator{ptr_ - n};
        }

        friend Iterator operator-(difference_type n, Iterator other) {
            return other - n;
        }

        difference_type operator-(Iterator it) const { return ptr_ - it.ptr_; }

        friend bool operator==(const Iterator& lhs, const Iterator& rhs) {
            return lhs.ptr_ == rhs.ptr_;
        }

        friend bool operator!=(const Iterator& lhs, const Iterator& rhs) =
            default;

        friend bool operator<(const Iterator& lhs, const Iterator& rhs) {
            return lhs.ptr_ < rhs.ptr_;
        }

        Iterator& operator+=(difference_type n) {
            ptr_ += n;
            return *this;
        }

        Iterator& operator-=(difference_type n) {
            ptr_ -= n;
            return *this;
        }

        friend std::strong_ordering operator<=>(
            const Iterator& lhs, const Iterator& rhs) = default;

      private:
        Iterator(T* ptr) : ptr_(ptr) {}

        friend class Vector<T>;

        T* ptr_;
    };

    //// Senior way
    // using iterator = T*;
    // using const_iterator = const T*;
    //// Junior way
    using iterator = Iterator<false>;
    using const_iterator = Iterator<true>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    iterator begin() { return {arr_}; }
    iterator end() { return {arr_ + size_}; }

    const_iterator begin() const { return {arr_}; }
    const_iterator end() const { return {arr_ + size_}; }

    const_iterator cbegin() const { return {arr_}; }
    const_iterator cend() const { return {arr_ + size_}; }

    reverse_iterator rbegin() { return reverse_iterator(end()); }
    reverse_iterator rend() { return reverse_iterator(arr_); }

    const_reverse_iterator rbegin() const {
        return const_reverse_iterator(arr_ + size_);
    }
    const_reverse_iterator rend() const { return const_reverse_iterator(arr_); }

    const_reverse_iterator crbegin() const {
        return const_reverse_iterator(arr_ + size_);
    }
    const_reverse_iterator crend() const {
        return const_reverse_iterator(arr_);
    }

    //  private:
    T* arr_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

int main() {
    std::vector<int>::reverse_iterator it;
    std::vector<int>::const_reverse_iterator cit;

    using RevIter = std::vector<int>::reverse_iterator;
    using MyIter = Vector<int>::iterator;
    using MyRevIter = Vector<int>::reverse_iterator;

    static_assert(std::is_base_of_v<
                  std::random_access_iterator_tag,
                  std::iterator_traits<RevIter>::iterator_category>);

    static_assert(std::is_base_of_v<
                  std::random_access_iterator_tag,
                  std::iterator_traits<MyRevIter>::iterator_category>);

    static_assert(std::random_access_iterator<RevIter>);  // More general check
                                                          // with concepts
    static_assert(std::random_access_iterator<MyIter>);
    // static_assert(std::random_access_iterator<MyRevIter>);

    using MyIter = Vector<int>::iterator;
    using MyRevIter = Vector<int>::reverse_iterator;
    static_assert(std::random_access_iterator<RevIter>);
    static_assert(std::random_access_iterator<MyIter>);

    Vector<int> v;
    v.PushBack(1);
    v.PushBack(3);
    v.PushBack(2);
    std::sort(v.rbegin(), v.rend());
    for (auto& val : v) {
        std::cout << val << " ";
    }
}
