#ifndef VIDEO_BUFFER_HPP
#define VIDEO_BUFFER_HPP

#include <array>
#include <cstdint>

namespace chip8
{
    class Video
    {
    public:
        std::array<std::uint32_t, 64 * 32> videoBuffer = {0};

        /// \brief Set the entire video buffer to zeros
        constexpr void clear() noexcept;
    };

    constexpr void Video::clear() noexcept
    {
        videoBuffer.fill(0);
    }
}

#endif