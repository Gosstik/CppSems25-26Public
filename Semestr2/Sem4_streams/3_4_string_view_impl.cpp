#include <cstddef>
#include <cstring>
#include <iostream>
#include <string>
#include <string_view>

struct StringView {
  public:
    StringView() = default;
    StringView(const char* str) : data_(str), size_(strlen(str)) {}
    StringView(const std::string& str) : data_(str.data()), size_(str.size()) {}

    StringView(const StringView& other) = default;

  private:
    const char* data_ = nullptr;
    size_t size_ = 0;
};

int main() {}
