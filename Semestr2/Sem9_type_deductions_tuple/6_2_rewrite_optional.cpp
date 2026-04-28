#include <optional>
#include <stdexcept>

// 4 versions of operator*() depending on value category
// same for Value()

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

    T& operator*() & { return reinterpret_cast<T&>(*val_); }

    const T& operator*() const& { return reinterpret_cast<const T&>(*val_); }

    T&& operator*() && { return reinterpret_cast<T&&>(*val_); }

    const T&& operator*() const&& { return reinterpret_cast<const T&&>(*val_); }

    ////////////////////////////////////////

    T& Value() & {
        if (!exists_) {
            throw std::bad_optional_access();
        }
        return reinterpret_cast<T&>(*val_);
    }

    // const T& Value() const & {}

    T& ValueOr(const T& other) {
        return exists_ ? reinterpret_cast<T&>(*val_) : other;
    }

  private:
    alignas(T) char val_[sizeof(T)]{};
    bool exists_ = false;
};
