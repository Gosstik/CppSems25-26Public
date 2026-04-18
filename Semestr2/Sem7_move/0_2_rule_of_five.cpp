#include <iostream>

struct String {
    String() = default;

    String(const String& other): size_(0) {
        // ...
    }

    String& operator=(const String& other) {
        // ...
    }

    String(String&& other): data_(other.data_) {
        size_ = other.size_;
        cap_ = other.cap_;

        other.data_ = nullptr;
        size_ = 0;
        cap_ = 0;
    }

    void Swap(String& other) {}

    String& operator=(String&& other) {
        if (this == &other) {
            return *this;
        }

        String s(std::move(other));
        // String s(1);
        Swap(s);
        return *this;
    }

    char* data_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

int main() {

}
