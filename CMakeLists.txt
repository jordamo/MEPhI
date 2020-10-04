cmake_minimum_required(VERSION 3.13)

project(xnum VERSION 1.0.0)

set ( CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
set(GTEST_ROOT google_test/googletest)
add_library(gtest STATIC
    ${GTEST_ROOT}/src/gtest_main.cc
    ${GTEST_ROOT}/src/gtest-all.cc
  )

target_include_directories(gtest PUBLIC ${GTEST_ROOT}/include)
target_include_directories(gtest PRIVATE ${GTEST_ROOT})

set(lib
    lib/xnum.cpp
  )

add_library(libs SHARED ${lib})
target_include_directories(libs PUBLIC lib/includes)

add_executable(main src/main)
add_executable(tests tests/static_test.cpp)
target_link_libraries(main libs)
target_link_libraries(tests libs gtest)
