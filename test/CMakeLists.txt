add_executable(MemoryTest)

find_package(GTest REQUIRED COMPONENTS gtest_main gmock_main)

target_link_libraries(MemoryTest
    PRIVATE
        GTest::gtest_main
        GTest::gmock_main
)

target_include_directories(MemoryTest PUBLIC "${PROJECT_SOURCE_DIR}/include")

target_sources(MemoryTest
    PUBLIC
        MemoryTest.cpp
    PRIVATE
        "${PROJECT_SOURCE_DIR}/include/Memory.hpp"
)

target_compile_features(MemoryTest PRIVATE cxx_std_17)

target_compile_options(MemoryTest PRIVATE -Wall -Wextra -Werror)
