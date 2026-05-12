#include <any>
#include <iostream>
#include <vector>

// The most tricky thing is to write dtor.

class Any {
  private:
    struct Base {
        virtual Base* GetCopy() const = 0;
        virtual ~Base() = 0;
    };

    template <typename T>
    struct Derived : Base {
        Derived(const T& value) : value_(value) {}
        Derived(T&& value) : value_(std::move(value)) {}
        ~Derived() override = default;

        Base* GetCopy() const override { return new Derived(value_); }

        T value_;
    };

  public:
    Any() = default;

    template <typename T>
    Any(const T& value) : ptr_(new Derived<T>(value)) {}

    Any(const Any& other) : ptr_(other.ptr_->GetCopy()) {}

    template <typename T>
    Any& operator=(const Any& other) {
        // TODO
    }

    ~Any() { delete ptr_; }

  private:
    template <typename T>
    friend T& AnyCast(Any& a);

    Base* ptr_;
};

////////////////////////////////////////////////////////////////////////////////

// any_cast

template <typename T>
T& AnyCast(Any& a) {
    // TODO: remove const
    auto* p = dynamic_cast<Any::Derived<std::remove_reference_t<T>>*>(a.ptr_);
    if (p == nullptr) {
        throw std::bad_any_cast();
    }
    return p->value_;
}

////////////////////////////////////////////////////////////////////////////////

int main() {
    std::any a = 5;

    a = "abc";
    std::cout << std::any_cast<const char*&>(a) << '\n';

    a = 3.14;
    std::cout << std::any_cast<double&>(a) << '\n';

    a = std::vector<int>{1, 2, 3};
    std::cout << std::any_cast<std::vector<int>&>(a)[0] << '\n';

    std::cout << std::flush;

    a = 2.0;
    // wrong cast, throws std::bad_any_cast
    std::cout << std::any_cast<int>(a) << '\n';
}
