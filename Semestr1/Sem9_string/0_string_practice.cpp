#include <iostream>
#include <string>
#include <algorithm>

#include <cstring>
#include <sstream>

// 1) Member initializer list (init values before ctor)
// 2) Delegation ctor - S(n, c) + std::fill, S(const char*) + std::copy
// 3) Copy/operator= (before, do not implement)
// 4) ==, <, >, <=
// 5) Size + const
// 6) [] + const
// 7) operator+ (with signature of +=)
// 8) << and >>
// 9)

struct A {
    int i;
};

struct S {
    // Initializer list
    S(int& other): x(other), a{1} {
    }

    // S(int& other) {
    //     x = other;
    //     a = A(1);
    // }

    int& x;
    // int z;
    const A a;
};

class String {
    public:

    String();
    String(const char* str): String(strlen(str)) {
        std::copy(str, str + size_ + 1, buf_);
        // for (size_t i = 0; i <= size_; ++i) {
        //     buf_[i] = str[i]; // *(buf + i) = l;
        // }
    }
    // Delegating ctor
    String(size_t sz, char l): String(sz) {
        std::fill(buf_, buf_ + sz, l);
        // for (size_t i = 0; i < sz; ++i) {
        //     buf_[i] = l; // *(buf + i) = l;
        // }
        buf_[sz] = '\0';
    }

    String(size_t sz): size_(sz), cap_(sz), buf_(new char[sz + 1]) {}

    ~String() {
        delete[] buf_;
    }

    size_t Size() const {
        return size_;
    }

    char& operator[](size_t i) {
        return buf_[i];
    }

    // String& operator+=(const String& s) {

    // }

    const char& operator[](size_t i) const {
        return buf_[i];
    }

    // char operator[](size_t i) const {
    //     return buf_[i];
    // }

    // bool operator<(String other) {
    //     return true;
    // }

    const char* Data() const {
        return buf_;
    }

    void PushBack(char c) {
    }

    private:

    friend bool operator<(const String& s1, const String& s2) {
        if (s1.size_ != s2.size_) {
            return false;
        }
        return false;
    }

    friend std::istream& operator>>(std::istream& is, String& s);


    size_t size_ = 0;
    size_t cap_ = 0;
    char* buf_ = nullptr;
};

bool operator>(const String& s1, const String& s2) {
    return s2 < s1;
}

bool operator<=(const String& s1, const String& s2) {
    return !(s2 > s1);
}

std::ostream& operator<<(std::ostream& os, const String& s) {
    return os << s.Data();
    // for (size_t i = 0; i < s.Size(); ++i) {
    //     os << s[i];
    // }
    // return os;
}

std::istream& operator>>(std::istream& is, String& s) {
    char tmp{};
    while (is.get(tmp) && std::isspace(tmp) != 0) {
    }
    if (!is) {
        return is;
    }
    s.PushBack(tmp);
    while (is.get(tmp) && std::isspace(tmp) == 0) {
        s.PushBack(tmp);
    }

    if (is) {
        is.unget();
        return is;
    }
    is.unget();
    is.get(tmp);
    if (std::isspace(tmp) != 0) {
        is.unget();
        return is;
    }
    return is;
}

int main() {
    // String s1;
    // const String s2(10, 'f');
    // std::cout << s2.Size() << '\n';
    // // std::cout << (s1 < "abc") << '\n';
    // // std::cout << ("abc" < s1) << '\n';

    // std::string tmp;
    // tmp[10] = 'a';

    // String s1;
    // const String& s2 = s1;
    // const char& c = s2[0];
    // std::cout << c << '\n';
    // s1[0] = 'd';
    // std::cout << c << '\n'; // d

    // std::cout << s1;

    std::string s;
    std::stringstream ss("   123   ");
    ss >> s;
    std::cout << s << '\n';

    // std::string s("abc\0def");
    // std::cout << s << '\n';
    // const char* str = "hgf";
    // std::cout << str << str << str;
    // std::cin >> s;

    // char* c;
    // std::cin >> c;

    // s1[10] = 't';

    // const String cs1;
    // std::cout << cs1[10] << '\n';
    // cs1[10] = 'f';
}
