find_package(GTest REQUIRED COMPONENTS gtest_main gmock_main)

add_executable(MemoryTest MemoryTest.cpp)

target_compile_features(MemoryTest PRIVATE cxx_std_17)

target_compile_options(MemoryTest PRIVATE -Wall -Wextra -Werror)

target_link_libraries(MemoryTest
    PRIVATE
        GTest::gtest_main
        GTest::gmock_main
)
