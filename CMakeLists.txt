# Copyright (c) 2026 Gubarger. All Rights Reserved.

cmake_minimum_required(VERSION 3.2)
project(Gubash VERSION 1.0.0)

# C++
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Auto installing Google tests
include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.tar.gz
)

option(BUILD_TESTS "Build tests" ON)

if (BUILD_TESTS)
  FetchContent_MakeAvailable(googletest)
endif()

# Main program file
add_executable(${PROJECT_NAME}
  source/main.cpp
  source/memory/slab.cpp
  source/memory/router.cpp
  source/memory/arena.cpp
  source/memory/layout.cpp

  source/utils/fgstring.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/source
)

# Tests
if(BUILD_TESTS)
  add_executable(Gubash_tests
    tests/testMemory.cpp
    tests/testString.cpp

    source/memory/layout.cpp
    source/memory/router.cpp
    source/memory/slab.cpp
    source/memory/arena.cpp

    source/utils/fgstring.cpp
  )

  target_link_libraries(Gubash_tests PRIVATE gtest_main)

  enable_testing()
  add_test(NAME GubashTests COMMAND Gubash_tests)

  find_program(VALGRIND valgrind)
  if(VALGRIND)
    add_test(NAME MemoryLeakTests
      COMMAND valgrind
      --leak-check=full
      --error-exitcode=1
      ./Gubash_tests
    )
  endif()
endif()
