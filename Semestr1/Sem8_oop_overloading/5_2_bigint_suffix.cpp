#include <cstddef>

//// In BigInteger you have to define:
// ( unsigned long long int )
// ( const char*, std::size_t )

class BigInteger {
  public:
    BigInteger() = default;
    template <typename T>
    BigInteger(T val) {}  // for all integer types
    explicit BigInteger(const char*) {}

    friend BigInteger operator""_bi(const char* str, size_t str_len);

  private:
    BigInteger(const char* str, size_t str_len) {}
};

BigInteger operator""_bi(const char* str, size_t str_len) {
    return {str, str_len};
}

BigInteger operator""_bi(unsigned long long val) { return val; }

int main() {}
