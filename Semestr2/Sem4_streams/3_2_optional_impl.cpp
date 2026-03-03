#include <cstdint>
#include <iostream>
#include <optional>

struct S {
    int a;
    // double b1;
    // double b2;
    // double b3;
    char c;
};

static_assert(sizeof(std::optional<bool>) == 2 * sizeof(bool));
static_assert(sizeof(std::optional<uint16_t>) == 2 * sizeof(uint16_t));
static_assert(sizeof(std::optional<uint32_t>) == 2 * sizeof(uint32_t));
static_assert(sizeof(std::optional<uint64_t>) == 2 * sizeof(uint64_t));
static_assert(
    sizeof(std::optional<S>) == sizeof(S) + alignof(S));  // common case

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

    T& operator*() { return reinterpret_cast<T&>(*val_); }

    const T& operator*() const { return reinterpret_cast<const T&>(*val_); }

    T& Value() {
        if (!exists_) {
            throw std::bad_optional_access();
        }
        return reinterpret_cast<T&>(*val_);
    }

    T& ValueOr(const T& other) {
        return exists_ ? reinterpret_cast<T&>(*val_) : other;
    }

  private:
    alignas(T) char val_[sizeof(T)]{};
    bool exists_ = false;
};

// TODO: ctor from nullopt
struct nullopt_t {};  // NOLINT
nullopt_t nullopt;

int main() {
    Optional<int> opt_int;
    // TODO: tests
}
