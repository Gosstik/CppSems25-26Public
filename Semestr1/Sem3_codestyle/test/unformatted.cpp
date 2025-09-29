// clang-format off

#include <vector>
#include <iostream>
#include <cstddef>

#include "hakhfw.h"



struct S {
private:
    int x_ = 0;   
  int y_ = 5;

  public:
    int z = 10;
};



void FooFunction(size_t first_argument, int second_argument, bool third_arg, char fourth) {}

void FooFunction(size_t first_argument, int second_argument, bool third_argument, bool fourth_argumment) {}

int main()
{
  std::vector <int> vec;

  int x = 0;
  int *px = &x;
  int &rx = x;

  std::cout<<  x << '\n'
  ;

  if (x == 0) { x += 10; }

  // AlignOperands: Align or true
  size_t my_very_long_counter = 20;
  size_t another_very_long_counter = 10;
  size_t common_very_long_multiplier = 3;
  size_t one_line = my_very_long_counter * common_very_long_multiplier + my_very_long_counter;

  size_t multi_line = my_very_long_counter * common_very_long_multiplier + another_very_long_counter * common_very_long_multiplier;
}

// clang-format on
