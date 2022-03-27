cmake_minimum_required(VERSION 3.16)

project(fixed_point VERSION 1.0)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_STANDARD_REQUIRED True)

configure_file(fpConfig.h.in fpConfig.h)

add_library(fixed_point INTERFACE)

target_include_directories(fixed_point INTERFACE fixed_point)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
include(GoogleTest)

add_executable(fixed_point-test
  tests/arithmetic.cpp
)

set_target_properties(fixed_point-test PROPERTIES CXX_STANDARD 14)
target_link_libraries(fixed_point-test PRIVATE fixed_point gtest_main)
gtest_add_tests(TARGET fixed_point-test)



