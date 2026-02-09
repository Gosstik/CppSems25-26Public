#include <cctype>  // isdigit, isspace
#include <format>
#include <iostream>
#include <sstream>

// TODO: getchar_unlocked

////////////////////////////////////////////////////////////////////////////////

// Util

bool IsSign(char c) {
  return c == '+' || c == '-';
}

bool IsDigit(char c) {
  return isdigit(c) != 0;
}

class String {
 public:
  String() = default;
  String(const char* str) : str(str) {}  // NOLINT
  void push_back(char c) {               // NOLINT
    str.push_back(c);
  }

  std::string str;
};

////////////////////////////////////////////////////////////////////////////////

// Impl

std::istream& operator>>(std::istream& is, String& val) {
  char ch{};

  // ignore whitespaces
  while (is.get(ch) && isspace(ch) != 0) {
  }

  if (!is) {
    return is;
  }
  val.push_back(ch);

  while (is.get(ch) && isspace(ch) == 0) {
    val.push_back(ch);
  }
  // TODO: use unget()
  std::cout << "'" << val.str << "'";

  return is;
}

////////////////////////////////////////////////////////////////////////////////

// Test

void Test(std::string input, std::string expected) {
  String val;
  std::stringstream ss(input);
  std::cout << std::format("Expected:\t'{}'\n", expected);
  std::cout << "Actual:\t\t";
  ss >> val;
  std::cout << "\n-----------------\n";
}

int main() {
  Test("a", "a");
  Test("abc", "abc");
  Test(" abc", "abc");
  Test("  abc ", "abc");
  Test(" \n\t ab  ", "ab");
  Test(" 234 abc", "234");
}
