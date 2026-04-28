#include <optional>
#include <stdexcept>
#include <utility>

// Use deducing this (since c++23) and write 1 version instead of 4

template <typename T>
class Optional {
  public:
    Optional() = default;

    // NOLINTNEXTLINE
    Optional(const T& new_val) : exists_(true) { new (val_) T(new_val); }

    ~Optional() {
        if (exists_) {
            reinterpret_cast<T*>(val_)->~T();
        }
    }

    bool HasValue() const { return exists_; }

    explicit operator bool() const { return exists_; }

    ////////////////////////////////////////

    template <typename Self>
    decltype(auto) operator*(this Self&& self) {
        using Result = decltype(std::forward_like<Self>(std::declval<T>()));
        return reinterpret_cast<Result>(*self.val_);
    }

    ////////////////////////////////////////

    decltype(auto) Value(this auto&& self) {
        using Result =
            decltype(std::forward_like<decltype(self)>(std::declval<T>()));
        if (!self.exists_) {
            throw std::bad_optional_access();
        }
        return reinterpret_cast<Result>(*self.val_);
    }

    // void Foo(this auto self) // accept self by value !!!

    ////////////////////////////////////////

    T& ValueOr(const T& other) {
        return exists_ ? reinterpret_cast<T&>(*val_) : other;
    }

  private:
    alignas(T) char val_[sizeof(T)]{};
    bool exists_ = false;
};

int main() {
    Optional<int> a(1);
    int& la = *a;
    int&& ra = *std::move(a);
}
