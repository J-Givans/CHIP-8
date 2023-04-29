add_executable(Tests)

find_package(GTest REQUIRED COMPONENTS gtest_main gmock_main)

target_link_libraries(Tests
    PRIVATE
        GTest::gtest_main
        GTest::gmock_main
)

target_include_directories(Tests PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(Tests
    PUBLIC
        MemoryTest.cpp
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/Memory.hpp"
)

target_compile_features(Tests PRIVATE cxx_std_17)

target_compile_options(Tests PRIVATE -Wall -Wextra -Werror)
