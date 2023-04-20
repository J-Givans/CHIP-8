#ifndef VIDEO_BUFFER_HPP
#define VIDEO_BUFFER_HPP

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
    };

    constexpr void Video::clear() noexcept
    {
        videoBuffer.fill(0);
    }
}

#endif