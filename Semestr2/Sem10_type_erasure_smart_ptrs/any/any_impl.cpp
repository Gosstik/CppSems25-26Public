#include <any>
#include <iostream>

class Any {
    struct BaseInner {
        virtual ~BaseInner() = default;
        virtual BaseInner* GetCopy() = 0;
    };

    template <typename T>
    struct DerivedInner : BaseInner {
        T value;

        // TODO: why commenting doesn't compile
        DerivedInner(T val) : value(val) {}

        BaseInner* GetCopy() override { return new DerivedInner<T>{value}; }
    };


    BaseInner* inner_ = nullptr;

  public:
    template <typename T>
    Any(T val) : inner_(new DerivedInner<T>{val}) {}

    Any(const Any& other) : inner_(other.inner_->GetCopy()) {}

    template <typename T>
    Any& operator=(T val) {
        delete inner_;
        inner_ = new DerivedInner<T>(val);
        return *this;
    }

    template <typename T>
    T& Get() {
        auto p = dynamic_cast<DerivedInner<T>*>(inner_);
        if (!p) {
            throw std::bad_any_cast();
        }
        return p->value;
    }
};

template <typename T>
void Foo() {
    Any a = T();
    a.Get<T>();
}

int main() { Foo<int>(); }
