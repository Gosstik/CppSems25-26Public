cmake_minimum_required(VERSION 3.20)
project(DebugWithClion)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-fsanitize=address)
add_link_options(-fsanitize=address)

add_executable(main main.cpp)
add_executable(debug_simple debug_simple.cpp)
add_executable(debug_merge_sort debug_merge_sort.cpp)
add_executable(A A.cpp)
add_executable(B B.cpp)
# add_executable(C C.cpp)
# ...
