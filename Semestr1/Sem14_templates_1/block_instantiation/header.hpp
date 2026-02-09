#pragma once

#include <iostream>

template <typename T>
extern void TFunc(T val) {
  std::cout << "val = " << val << '\n';
}

extern template void TFunc<int>(int val);

// block instantiation
