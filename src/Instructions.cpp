#include "Instructions.hpp"

namespace chip8
{
    constexpr void op00E0(Video& video) noexcept
    {
        video.clear();
    }
}