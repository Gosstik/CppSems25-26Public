#include <iostream>
#include <stdexcept>

// try with -fsanitize=address

template <typename T>
struct UniquePtr {
    UniquePtr(T* p) : p(p) {}  // NOLINT

    UniquePtr(const UniquePtr&) = delete;
    UniquePtr& operator=(const UniquePtr&) = delete;
    ~UniquePtr() { delete p; }

    T& operator*() { return *p; }

    T* p;
};

struct BadPtrWrapper {
    BadPtrWrapper(int* p) : p(p) {}  // NOLINT
    ~BadPtrWrapper() { delete p; }

    int& operator*() {  // NOLINT
        return *p;
    }

    int* p;
};

////////////////////////////////////////////////////////////////////////////////

template <typename PtrImpl>
void Bar(PtrImpl wrapper) {
    if (*wrapper % 2 == 1) {
        throw std::invalid_argument("only even values are acceptable");
    }
    *wrapper.p *= 2;
}

void Foo(int x) {
    // BadPtrWrapper pw = BadPtrWrapper(new int(x));
    UniquePtr pw = UniquePtr(new int(x));
    Bar(pw);
    //// no delete!
}

int main() {
    try {
        Foo(0);
        Foo(1);
    } catch (const std::exception& err) {
        std::cout << "Foo failed: " << err.what() << '\n';
    }
}
