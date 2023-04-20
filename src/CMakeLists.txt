target_link_libraries(app
    PRIVATE
        Microsoft.GSL::GSL
)

target_compile_features(app PRIVATE cxx_std_17)

target_compile_options(app PRIVATE -Wall -Wextra -Werror -Wundef -Wconversion)

target_include_directories(app PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_sources(app 
    PRIVATE
        FontSet.hpp
        FontSet.cpp
        Memory.hpp
        Memory.cpp
        Video.hpp
        Video.cpp
)