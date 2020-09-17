cmake_minimum_required(VERSION 3.2)

project(ProjestWithGTest
        VERSION 1.0
        DESCRIPTION "Test taks_1"
)

add_subdirectory(
    "${CMAKE_CURRENT_SOURCE_DIR}/google_test"
    "googletest"
)

add_executable(
    task
    main.cpp
    prog.cpp
)

add_executable(
    tests
    tests/test.cpp
)


target_link_libraries(
    tests PRIVATE
    gtest gtest_main
        )

target_compile_options(
        task PRIVATE
        -Wall -Wextra -pedantic -Warror
        )

target_compile_options(
        tests PRIVATE
        -Wall -Wextra -pedantic -Warror)
