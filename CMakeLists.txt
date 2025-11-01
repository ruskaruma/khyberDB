cmake_minimum_required(VERSION 3.20)
project(khyberdb VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_TESTING "Build the testing tree" ON)
option(BUILD_BENCHMARKS "Build benchmarks" ON)
option(BUILD_EXAMPLES "Build examples" OFF)

include(FetchContent)

# Fetch spdlog for logging
FetchContent_Declare(
  spdlog
  GIT_REPOSITORY https://github.com/gabime/spdlog.git
  GIT_TAG v1.14.1
)
FetchContent_MakeAvailable(spdlog)

# Fetch CLI11 for argument parsing
FetchContent_Declare(
  CLI11
  GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
  GIT_TAG v2.5.0
)
FetchContent_MakeAvailable(CLI11)

# Configure compilation options
if(MSVC)
  add_compile_options(/W4 /permissive-)
else()
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Enable sanitizers for debug builds
if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND NOT MSVC)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")
endif()

# Include directories
include_directories(src)

# Library sources
set(SOURCES
  src/db.cpp
)

add_library(khyberdb_lib ${SOURCES})

target_link_libraries(khyberdb_lib PUBLIC
  spdlog::spdlog
)

# Main executable
add_executable(khyberdb
  src/main.cpp
)

target_link_libraries(khyberdb
  PUBLIC
  khyberdb_lib
  CLI11::CLI11
)

# Testing
if(BUILD_TESTING)
  enable_testing()
  
  FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
  )
  FetchContent_MakeAvailable(googletest)
  
  add_executable(test_khyberdb
    src/test_db.cpp
  )
  
  target_link_libraries(test_khyberdb
    khyberdb_lib
    GTest::gtest
    GTest::gtest_main
  )
  
  include(GoogleTest)
  gtest_discover_tests(test_khyberdb)
endif()

# Benchmarks
if(BUILD_BENCHMARKS)
  FetchContent_Declare(
    benchmark
    GIT_REPOSITORY https://github.com/google/benchmark.git
    GIT_TAG v1.9.0
  )
  FetchContent_MakeAvailable(benchmark)
  
  add_executable(bench_khyberdb
    src/bench_db.cpp
  )
  
  target_link_libraries(bench_khyberdb
    khyberdb_lib
    benchmark::benchmark
    benchmark::benchmark_main
  )
endif()

# Installation
install(TARGETS khyberdb khyberdb_lib
  RUNTIME DESTINATION bin
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)

