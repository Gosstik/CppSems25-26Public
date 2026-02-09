#include <algorithm>
#include <cstring>
#include <iostream>

// Rule Of Three --- rule of thumb, not a standard term

// Ctor
// Copy ctor
// Dtor
// operator=()
// copy-and-swap idiom: 1. no code duplication 2. strong exception guaranty
// const and nonconst methods (size, capacity, ...)
// operator[]: const and non-const methods
// = default(), = delete()
// operator<<() and operator>>()

namespace detail {

bool IsSpace(char c) {
    return std::isspace(static_cast<unsigned char>(c)) != 0;
}

void IgnoreSpaces(std::istream& istream) {
    using CharTraits = std::istream::traits_type;

    char c = '\0';
    while (istream.good()) {
        c = CharTraits::to_char_type(istream.get());
        if (!IsSpace(c)) {
            istream.unget();
            return;
        }
    }
}

}  // namespace detail

class String {
  public:
    // Explicitly declared, implicitly defined
    // String() = default;

    String() : String(static_cast<size_t>(0)) {}

    String(int n) {}

    String(const char* str) : String(strlen(str)) {
        std::copy(str, str + size_, data_);
    }

    String(size_t n, char c) : String(n) {
        // memset(data_, c, n);
        std::fill(data_, data_ + size_, c);
    }

    String(const String& other) : String(other.size_) {
        // this->String(other.sz_); // no, god, please, noooo !!!
        // memcpy(arr_, other.arr_, sz_);
        std::copy(other.data_, other.data_ + other.size_, data_);
    }

    // String& operator=(const String& other) {
    //     if (this == &other) {
    //         return *this;
    //     }
    //     /// dtor cannot be called twice on the same object
    //     // this->~String(); // !!! WRONG
    //     delete[] data_;
    //     data_ = new char[other.size_ + 1]{};
    //     std::copy(other.data_, other.data_ + other.size_, data_);
    //     size_ = other.size_;
    //     cap_ = other.cap_;

    //     return *this;
    // }

    // Copy And Swap (exception safe)
    String& operator=(const String& other) {
      if (this == &other) {
        return *this;
      }
      String copy = other;  // 'other' can be passed by value
      Swap(copy);
      return *this;
    }

    void Swap(String& other) {
        std::swap(data_, other.data_);
        std::swap(size_, other.size_);
        std::swap(cap_, other.cap_);
    }

    // Spaceship operator
    // https://en.cppreference.com/w/cpp/language/default_comparisons

    std::weak_ordering operator<=>(const String& other) const {
        size_t min_size = std::min(size_, other.size_);
        for (size_t i = 0; i < min_size; ++i) {
            if (data_[i] == other.data_[i]) {
                continue;
            }
            return (data_[i] < other.data_[i]) ? std::weak_ordering::less
                                               : std::weak_ordering::greater;
        }

        if (size_ == other.size_) {
            return std::weak_ordering::equivalent;
        }
        return (size_ < other.size_) ? std::weak_ordering::less
                                     : std::weak_ordering::greater;
    }

    friend bool operator==(const String& lhs, const String& rhs) {
        if (lhs.size_ != rhs.size_) {
            return false;
        }
        return (lhs <=> rhs) == std::weak_ordering::equivalent;
    }

    // // No need, is generated automatically
    // friend bool operator!=(const String& lhs, const String& rhs) {
    //     return !(lhs == rhs);
    // }

    // End of spaceship operator

    char& operator[](size_t index) { return data_[index]; }

    const char& operator[](size_t index) const { return data_[index]; }

    size_t Size() const { return size_; }

    void Clear() {
        // impl...
    }

    void PushBack(char c) {
        // impl...
    }

    char* Data() const { return data_; }

    ~String() { delete[] data_; }

  private:
    explicit String(size_t size)
        : data_(new char[size + 1]{}),
          size_(size),
          cap_(size) {}

    char* data_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

// operator>>()

std::istream& operator>>(std::istream& istream, String& str) {
    using CharTraits = std::istream::traits_type;

    detail::IgnoreSpaces(istream);

    str.Clear();

    char c = '\0';
    while (istream.good()) {
        c = CharTraits::to_char_type(istream.get());
        if (!istream.good()) {
            break;
        }
        if (detail::IsSpace(c)) {
            istream.unget();
            break;
        }
        str.PushBack(c);
    }

    return istream;
}

// operator<<()

std::ostream& operator<<(std::ostream& ostream, const String& str) {
    ostream << str.Data();
    return ostream;
}

int main() {
    String s = s;  // call copy ctor
}
