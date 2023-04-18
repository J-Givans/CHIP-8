target_link_libraries(app
    PRIVATE
        Microsoft.GSL::GSL
        gtest::gtest
)

target_compile_features(app PRIVATE cxx_std_17)

target_compile_options(app PRIVATE -Wall -Wextra -Werror -Wundef -Wconversion)

target_include_directories(app PRIVATE "${PROJECT_SOURCE_DIR}/src")