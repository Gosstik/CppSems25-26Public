#include <iostream>
#include <string>

struct S {
    // Try to get s2 by value
    S(int a, std::string&& s1, std::string& s2): a(a), s1(std::move(s1)), s2(s2) {}

    int a;
    std::string s1;
    std::string s2;
};

template <typename T>
class Vector {
    public:

    template <typename... Args>
    void emplace_back(Args&&... args) {
        // reserve
        new (vals_ + size_) T(args...); // all args will be copied
        new (vals_ + size_) T(std::move(args)...); // invalidate references
        ++size_;
    }

    private:

    T* vals_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

int main() {
    Vector<S> v;

    std::string s;
    v.emplace_back(1, "hello", s);
}
