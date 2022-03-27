cmake_minimum_required(VERSION 3.16)

project(fp VERSION 1.0)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

option(USE_FIXED_POINT "Use FixedPoint Library" ON)

if(USE_FIXED_POINT)
  add_subdirectory(fixed_point)
  list(APPEND EXTRA_LIBS "fixed_point")
  list(APPEND EXTRA_INCLUDES "${PROJECT_SOURCE_DIR}/fixed_point")
  list(APPEND EXTRA_INCLUDE_DIRS "fixed_point")
  list(APPEND EXTRA_LINKS fixed_point )
endif()
configure_file(fpConfig.h.in fpConfig.h)

# add_subdirectory(fixed_point)
set_target_properties(fixed_point PROPERTIES LINKER_LANGUAGE CXX)

add_executable(fp
  test.cpp
  tests/arithmetic.cpp
)

target_link_libraries(fp PUBLIC fixed_point gtest_main)
target_include_directories(fp PUBLIC
                          ${PROJECT_BINARY_DIR}
                          ${EXTRA_INCLUDES}
                          )

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

include(GoogleTest)
gtest_add_tests(TARGET fp)