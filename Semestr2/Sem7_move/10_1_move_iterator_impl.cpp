#include <iostream>
#include <iterator>
#include <string>
#include <utility>
#include <vector>

// TODO

std::move_iterator<int> a();

template <typename It>
struct MoveIterator {
    MoveIterator() = default;
    MoveIterator(It other) : ptr_(other) {}
    MoveIterator& operator=(const MoveIterator& other) = default;
    ~MoveIterator() = default;

    using value_type = std::iterator_traits<It>::value_type;
    using reference = std::iterator_traits<It>::value_type&&;
    using pointer = std::iterator_traits<It>::value_type*;
    using iterator_category = std::iterator_traits<It>::iterator_category;
    using difference_type = std::iterator_traits<It>::difference_type;

    reference operator*() const { return std::move(*ptr_); }

    pointer operator->() const { return ptr_; }

    reference operator[](difference_type n) const { return std::move(ptr_[n]); }

    MoveIterator& operator++() {
        ++ptr_;
        return *this;
    }

    MoveIterator operator++(int) {
        MoveIterator copy = *this;
        ++(*this);
        return copy;
    }

    MoveIterator& operator--() {
        --ptr_;
        return *this;
    }

    MoveIterator operator--(int) {
        MoveIterator copy = *this;
        --(*this);
        return copy;
    }

    MoveIterator operator+(difference_type n) const {
        return MoveIterator{ptr_ + n};
    }

    friend MoveIterator operator+(difference_type n, MoveIterator other) {
        return other + n;
    }

    MoveIterator operator-(difference_type n) const {
        return MoveIterator{ptr_ - n};
    }

    friend MoveIterator operator-(difference_type n, MoveIterator other) {
        return other - n;
    }

    difference_type operator-(MoveIterator it) const { return ptr_ - it.ptr_; }

    friend bool operator==(const MoveIterator& lhs, const MoveIterator& rhs) {
        return lhs.ptr_ == rhs.ptr_;
    }

    friend bool operator!=(const MoveIterator& lhs, const MoveIterator& rhs) =
        default;

    friend bool operator<(const MoveIterator& lhs, const MoveIterator& rhs) {
        return lhs.ptr_ < rhs.ptr_;
    }

    MoveIterator& operator+=(difference_type n) {
        ptr_ += n;
        return *this;
    }

    MoveIterator& operator-=(difference_type n) {
        ptr_ -= n;
        return *this;
    }

    friend std::strong_ordering operator<=>(
        const MoveIterator& lhs, const MoveIterator& rhs) = default;

  private:
    It ptr_;
};

////////////////////////////////////////////////////////////////////////////////

struct S {
    S(std::string data) : data(std::move(data)) { std::cout << "S(string)\n"; }
    S(const S& other) : data(other.data) { std::cout << "S(const S&)\n"; }
    S(S&& other) noexcept : data(std::move(other.data)) {
        std::cout << "S(S&&)\n";
    }
    S& operator=(const S& other) {
        data = other.data;
        std::cout << "operator=(const S&)\n";
        return *this;
    }
    S& operator=(S&& other) noexcept {
        data = std::move(other.data);
        std::cout << "operator=(S&&)\n";
        return *this;
    }

    std::string data;
};

struct CopyOnly {
    CopyOnly(std::string data) : data(std::move(data)) {
        std::cout << "CopyOnly(string)\n";
    }

    CopyOnly(const CopyOnly& other) : data(other.data) {
        std::cout << "CopyOnly(const CopyOnly&)\n";
    }
    CopyOnly& operator=(const CopyOnly& other) {
        data = other.data;
        std::cout << "operator=(const CopyOnly&)\n";
        return *this;
    }

    CopyOnly(CopyOnly&& other) = delete;
    CopyOnly& operator=(CopyOnly&& other) = delete;

    std::string data;
};

struct MoveOnly {
    MoveOnly(std::string data) : data(std::move(data)) {
        std::cout << "MoveOnly(string)\n";
    }

    MoveOnly(const MoveOnly& other) = delete;
    MoveOnly& operator=(const MoveOnly& other) = delete;

    MoveOnly(MoveOnly&& other) noexcept : data(std::move(other.data)) {
        std::cout << "MoveOnly(MoveOnly&&)\n";
    }
    MoveOnly& operator=(MoveOnly&& other) noexcept {
        data = std::move(other.data);
        std::cout << "operator=(MoveOnly&&)\n";
        return *this;
    }

    std::string data;
};

////////////////////////////////////////////////////////////////////////////////

void TestS() {
    std::vector<S> v1{S("1"), S("2"), S("3")};
    std::cout << "-------------\nTest S:\n";
    // std::vector<S> v2(
    //     std::move_iterator(v1.begin()), std::move_iterator(v1.end())
    // );
    std::vector<S> v2(MoveIterator(v1.begin()), MoveIterator(v1.end()));
    std::cout << "-------------\n";
}

void TestCopyOnly() {
    std::vector<CopyOnly> v1{CopyOnly("1"), CopyOnly("2"), CopyOnly("3")};
    std::cout << "-------------\nTest CopyOnly:\n";
    // std::vector<CopyOnly> v2(std::move_iterator(v1.begin()),
    // std::move_iterator(v1.end())); // CE
    std::vector<CopyOnly> v2(v1.begin(), v1.end());  // OK
    std::cout << "-------------\n";
}

void TestMoveOnly() {
    std::vector<MoveOnly> v1;
    v1.emplace_back("1");
    v1.emplace_back("2");
    v1.emplace_back("3");
    std::cout << "-------------\nTest MoveOnly:\n";
    // std::vector<MoveOnly> v2(
    //     std::move_iterator(v1.begin()), std::move_iterator(v1.end())
    // );
    std::vector<MoveOnly> v2(MoveIterator(v1.begin()), MoveIterator(v1.end()));
    // std::vector<MoveOnly> v2(v1.begin(), v1.end());
    std::cout << "-------------\n";
}

int main() {
    // TestS();
    // TestCopyOnly();
    TestMoveOnly();
}
