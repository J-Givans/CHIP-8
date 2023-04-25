#ifndef VIDEO_BUFFER_HPP
#define VIDEO_BUFFER_HPP

#include "Registers.hpp"
#include "Memory.hpp"

#include <array>
#include <cstdint>

namespace chip8
{
    inline constexpr unsigned int VideoWidth = 64;
    inline constexpr unsigned int VideoHeight = 32;

    class Video
    {
    public:
        std::array<std::uint32_t, VideoWidth * VideoHeight> videoBuffer = {0};

        /// \brief Set the entire video buffer to zeros
        constexpr void clear() noexcept;

        /// \brief DRW Vx, Vy, nibble
        /// \brief Display n-byte sprite starting at memory location I at (Vx, Vy) and set VF = collision
        void opDxyn(Memory& memory, Registers& reg) noexcept;
    };

    constexpr void Video::clear() noexcept
    {
        videoBuffer.fill(0);
    }
}

#endif