#include <iostream>

struct String {
  public:
    String() = default;

    // Copy ctor
    String(const String& other)
        : buf_(AllocBuf(other.size_)),
          size_(other.size_),
          cap_(other.cap_) {}

    // Move ctor
    String(String&& other)
        : buf_(other.buf_),
          size_(other.size_),
          cap_(other.cap_) /*noexcept*/ {
        other.buf_ = nullptr;
        other.size_ = 0;
        other.cap_ = 0;
    }

    String& operator=(const String& other) {
        if (this == &other) {
            return *this;
        }
        String tmp(other);
        Swap(tmp);
        return *this;
    }

    String& operator=(String&& other) /*noexcept*/ {
        if (this == &other) {
            return *this;
        }
        String tmp(std::move(other));
        Swap(tmp);
        return *this;
    }

  private:
    char* AllocBuf(const size_t size) {
        return static_cast<char*>(operator new(size));
    }

    void Swap(String& other) {
        std::swap(buf_, other.buf_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }

    char* buf_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

int main() {}
