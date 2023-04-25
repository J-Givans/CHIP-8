target_link_libraries(app
    PRIVATE
        Microsoft.GSL::GSL
)

target_compile_features(app PRIVATE cxx_std_17)

target_compile_options(app PRIVATE -Wall -Wextra -Werror -Wundef -Wconversion)

target_include_directories(app PRIVATE "${PROJECT_SOURCE_DIR}/src")

target_sources(app 
    PRIVATE
        CPU.hpp
        CPU.cpp
        FontSet.hpp
        FontSet.cpp
        Instructions.hpp
        Instructions.cpp
        Keypad.hpp
        Keypad.cpp
        Memory.hpp
        Memory.cpp
        Registers.hpp
        Registers.cpp
        Stack.hpp
        Stack.cpp
        Timers.hpp
        Timers.cpp
        Video.hpp
        Video.cpp
)