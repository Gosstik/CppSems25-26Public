cmake_minimum_required(VERSION 3.28.0)
project(SafeTransform VERSION 0.1.0)

#-------------------------------------------------------------------------------

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  # GIT_TAG        v3.4.0 # or a later release
  GIT_TAG        v3.8.0
)

FetchContent_MakeAvailable(Catch2)

#-------------------------------------------------------------------------------

include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(tests "${CMAKE_CURRENT_SOURCE_DIR}/tests/test.cpp")
target_link_libraries(tests PRIVATE Catch2::Catch2WithMain)

