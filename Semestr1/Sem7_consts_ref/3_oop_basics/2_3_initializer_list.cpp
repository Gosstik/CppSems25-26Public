#include <algorithm>
#include <cstring>
#include <initializer_list>
#include <iostream>
#include <vector>

class String {
  public:
    // since C++11
    String(std::initializer_list<char> list)
        : data_(new char[list.size() + 1]),
          size_(list.size()),
          cap_(size_) {
        std::copy(list.begin(), list.end(), data_);
        data_[size_] = '\0';
    }

    ~String() { delete[] data_; }

  private:
    char* data_ = nullptr;
    size_t size_ = 0;
    size_t cap_ = 0;
};

int main() {
    {
        // What ctor and what is the difference?
        std::vector<int> v1 = {1, 2, 3, 4, 5};
        std::vector<int> v2{1, 2, 3, 4, 5};
    }

    {
        // initializer_list problem
        String s1 = {'a', 'b'};
        String s2{2, 'a'};  // ???
    }
}
