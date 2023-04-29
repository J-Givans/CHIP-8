find_package(Microsoft.GSL REQUIRED)
find_package(SFML 2.5.1 REQUIRED COMPONENTS sfml-system sfml-window sfml-graphics)

target_link_libraries(app
    PRIVATE
        Microsoft.GSL::GSL
        sfml-system
        sfml-window
        sfml-graphics
)

target_compile_features(app PRIVATE cxx_std_17)

target_compile_options(app PRIVATE -Wall -Wextra -Werror -Wundef -Wconversion)

target_include_directories(app PRIVATE "${PROJECT_SOURCE_DIR}/include")

target_sources(app 
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/CPU.hpp
        ${PROJECT_SOURCE_DIR}/include/FontSet.hpp
        ${PROJECT_SOURCE_DIR}/include/Instructions.hpp
        ${PROJECT_SOURCE_DIR}/include/Keypad.hpp
        ${PROJECT_SOURCE_DIR}/include/Memory.hpp
        ${PROJECT_SOURCE_DIR}/include/Registers.hpp
        ${PROJECT_SOURCE_DIR}/include/Stack.hpp
        ${PROJECT_SOURCE_DIR}/include/Timers.hpp
        ${PROJECT_SOURCE_DIR}/include/Video.hpp
        ${PROJECT_SOURCE_DIR}/include/Platform.hpp
    PRIVATE
        CPU.cpp
        FontSet.cpp
        Instructions.cpp
        Keypad.cpp
        Memory.cpp
        Registers.cpp
        Stack.cpp
        Timers.cpp
        Video.cpp
        Platform.cpp
)