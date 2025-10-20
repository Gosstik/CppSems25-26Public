#include <cassert>
#include <cmath>
#include <cstdio>
#include <format>
#include <iomanip>  // input/output manipulators
#include <iostream>

// More scanf flags: https://www.opennet.ru/man.shtml?topic=scanf&category=3

struct Timestamp {
  int year{};
  int month{};
  int day{};
  int hour{};
  int min{};
  int sec{};
  int tz_h{};
  int tz_m{};
};

void Snippets() {
  {
    // scanf

    int val = 0;
    printf("val = %d\n", val);  // std::cout

    char c_str[100]{};   // why 100?
    scanf("%s", c_str);  // std::cin
    printf("str = %s\n", c_str);

    float fl = 0.0;
    scanf("%f", &fl);
    printf("fl = %f\n", fl);

    int int_val = 0;
    scanf("%d", &int_val);
    printf("val = %d\n", int_val);

    size_t size_t_v{};
    float float_v{};
    double double_v{};
    scanf("%zu %f %lf", &size_t_v, &float_v, &double_v);
    printf(
        "size_t = %zu, float = %f, double = %lf\n",
        size_t_v,
        float_v,
        double_v);
    // compare printf with std::cout
    std::cout << "size_t = " << size_t_v << ", float = " << float_v
              << ", double = " << double_v << '\n';

    {
      // C style
      scanf("%[^\n]", c_str);  // read until '\n'
      scanf("%[^;]", c_str);   // read until ';' //? when it may be useful?
    }

    {
      // C++ style
      std::string cpp_str;
      std::cin >> cpp_str;                   // ? Difference with next line?
      std::getline(std::cin, cpp_str);       // read until '\n
      std::getline(std::cin, cpp_str, ';');  // read until ';'
    }

    {
      // Reading data: 2024-10-10T17:15:48+03:00 (run in terminal: date -Is)
      Timestamp ts;
      scanf(
          "%d-%d-%dT%d:%d:%d+%d:%d",
          &ts.year,
          &ts.month,
          &ts.day,
          &ts.hour,
          &ts.min,
          &ts.sec,
          &ts.tz_h,
          &ts.tz_m);

      ts.year += 1;
      if (ts.month == 12) {
        ts.month = 0;
        ts.day += 1;
      } else {
        ts.month += 1;
      }

      printf(
          "%d-%d-%dT%d:%d:%d+%d:%d\n",
          ts.year,
          ts.month,
          ts.day,
          ts.hour,
          ts.min,
          ts.sec,
          ts.tz_h,
          ts.tz_m);
      printf(
          "%04d-%02d-%02dT%02d:%02d:%02d+%02d:%02d\n",
          ts.year,
          ts.month,
          ts.day,
          ts.hour,
          ts.min,
          ts.sec,
          ts.tz_h,
          ts.tz_m);

      // No C++ style to replace scanf :(
    }
  }

  {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie();
    std::cout.tie();

    std::cout << "Enter password: ";
    // std::cout << std::flush; // manual flush to terminal
    std::string str;
    std::cin >> str;
    std::cout << "Password: " << str << '\n';
  }

  {
    // Partial replace for printf - Input/output manipulators from <iomanip>
    // More: https://en.cppreference.com/w/cpp/io/manip

    std::cout << "Booleans:\n";
    std::cout << "1: " << std::boolalpha << 1 << '\n'
              << "0: " << std::boolalpha << 0 << '\n';

    ////////////////////////////////////////////////////////////////////////////
    std::cout << '\n';

    std::cout << "Other base:\n";
    std::cout << "The number 42 in octal:   " << std::oct << 42 << '\n'
              << "The number 42 in decimal: " << std::dec << 42 << '\n'
              << "The number 42 in hex:     " << std::hex << 42 << '\n';

    std::cout << '\n';

    ////////////////////////////////////////////////////////////////////////////
    std::cout << "Floating point:\n";
    long double pi = 3.141592653589793;
    // long double pi = std::numbers::pi_v<long double>;

    auto default_precision = std::cout.precision();
    int max_precision = 15;
    // int max_precision = std::numeric_limits<long double>::digits10 + 1;

    std::cout << "default precision: " << default_precision << '\n'
              << "maximum precision: " << max_precision
              << "\n\n"
                 "precision: pi:\n";

    for (int p = 0; p <= max_precision; ++p) {
      std::cout << std::setw(2) << p << ":  " << std::setprecision(p) << pi
                << '\n';
    }

    std::cout << std::setprecision(default_precision);  // restore defaults
  }

  {
    // std::format (since C++20)
    // to use add -std=c++20 to clangd arguments
    // more format specifiers:
    // https://en.cppreference.com/w/cpp/utility/format/spec

    int id = 3;
    const char hello[] = "Hello";
    std::cout << std::format("{}, {}. My id = {}\n", hello, id, id);

    assert(std::format("{0:},{0:+},{0:-},{0: }", 1) == "1,+1,1, 1");  // signs

    float sqrt_2 = sqrt(2);                           // 1.414213562373095
    assert(std::format("{:.2f}", sqrt_2) == "1.41");  // precision = 2
    assert(
        std::format("{:7.3f}", sqrt_2) ==
        "  1.414");  // width = 7, precision = 3

    int val = 22;
    std::cout << std::format("id {:*<10d}\n", val);  // 22********
    std::cout << std::format("id {:#^10d}\n", val);  // ####22####
    std::cout << std::format("id {: >10d}\n", val);  //         22

    // quoted output
    // quoted: #include <iomanip>
    std::cout << "c: " << std::quoted("abc") << '\n';
    std::cout << "c: " << std::quoted(std::string(3, 'a')) << '\n';
  }
}

int main() {
  Snippets();
}
