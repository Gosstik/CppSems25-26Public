// Macroses are preprocess directives, they begin with # and do not end with ;

////////////////////////////////////////////////////////////////////////////////

// include

#include <cstdint>
#include <iostream>

void Func() { std::cout << "Its me\n"; }

// #include may be located at the middle of file
#include <vector>

void Func2() {
  std::vector<int> v = {1, 2, 3};
  std::cout << v[0] << '\n';
}

// include --- a stupid substitution of the file contents
void Foo() {
//   #include <deque> // CE
}

////////////////////////////////////////////////////////////////////////////////

// define

// Types
#define ull unsigned long long  // very poor

typedef unsigned long long Ull;  // better
using Ull = unsigned long long;  // best, except of naming :)

int Bar() {
  ull x = 0;
  Ull y = 1;
  Ull z = 2;
  return x + y + z;
}

// Values
#include <cmath>
#define MY_PI 3.14159265
#define N 10

const double pi = 3.14159265;

int Baz() {
  std::cout << MY_PI << std::endl;
  std::cout << M_PI << std::endl;
  std::cout << "M_PI" << std::endl;  // not so stupid as #include
  return M_PI;
}

// Functions
#define STUPID_MIN(a, b) a < b ? a : b
#define SMART_MIN(a, b) (((a) < (b)) ? (a) : (b))

// 1 + 1 < 2 + 3 ? 1 + 1 : 2 + 3

void CallMin() {
  int a1 = STUPID_MIN(1, 2);          // OK
  int a2 = STUPID_MIN(1 + 2, 2 + 3);  // OK
  // std::cout << STUPID_MIN(1, 2) << std::endl; // CE

  std::cout << SMART_MIN(1, 2) << std::endl;  // OK
}

// Concatenation
#define DEFINE_CONCAT(A, B) A##B

void Baz1() { std::cout << DEFINE_CONCAT(1, 2) << std::endl; }

// Mom's hackers
#define MAKE_INCLUDE(a, b) <a ## b>
#include MAKE_INCLUDE(str, ing)  // #include <string>

using String = std::string;

void TestString() {
  String a = "abc";
  String b = "def";
  std::cout << a + b << std::endl;
}

// Multiline functions
#define MIN_FUNC(type) \
  type min_func_##type(type a, type b) { return ((a) < (b)) ? (a) : (b); }

MIN_FUNC(int64_t);
MIN_FUNC(uint64_t);
MIN_FUNC(double);

void TestMinFunc() {
  std::cout << min_func_int64_t(1, 2) << '\n';
  std::cout << min_func_uint64_t(1ull, 2ull) << '\n';
  std::cout << min_func_double(1.2, 2.5) << '\n';
}

// Define in define
#define MIN_FUNC_NAME(type) min_func_decomposed_##type
#define MIN_FUNC_DECOMPOSED(type) \
  type MIN_FUNC_NAME(type)(type a, type b) { return SMART_MIN(a, b); }

MIN_FUNC_DECOMPOSED(int64_t);
MIN_FUNC_DECOMPOSED(uint64_t);
MIN_FUNC_DECOMPOSED(double);

// More multiline
// Suppress compiler warnings about unused variable/argument
#define MAYBE_UNUSED(x) \
  do {                  \
    (void)(x);          \
  } while (false)

void MyFunc() {
  int x = 0;
  MAYBE_UNUSED(x);
  int b = 0;
}

////////////////////////////////////////////////////////////////////////////////

// ifndef

#include <cassert>

// #define NDEBUG

#ifndef NDEBUG

#define MY_ASSERT(cond, error)                                              \
  do {                                                                      \
    if (!(cond)) {                                                          \
      std::cerr << "Assertion '" << #cond << "' failed: " << error << '\n'; \
      std::abort();                                                         \
    }                                                                       \
  } while (true)

#else

#define MY_ASSERT(cond, error) \
  do {                         \
    if (false) {               \
      bool to_ignore = cond;   \
      MAYBE_UNUSED(to_ignore); \
    }                          \
  } while (false)

#endif

#undef NDEBUG

void CheckAssert() {
  // RE when NDEBUG is defined
  assert(1 == 1 && "abcde");
  MY_ASSERT(1 == 1, "OK");
  MY_ASSERT(1 == 2, "1 != 2");  // RE only when NDEBUG is defined
}

////////////////////////////////////////////////////////////////////////////////

// define guards
// See 'compilation_examples' folder

int main() {
  // For you to play :)
}
