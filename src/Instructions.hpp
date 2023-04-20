#ifndef INSTRUCTIONS_HPP
#define INSTRUCTIONS_HPP

#include "Video.hpp"

namespace chip8
{
    /// \brief Clear the video buffer
    constexpr void op00E0(Video& video) noexcept;
}

#endif