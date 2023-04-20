#ifndef VIDEO_BUFFER_HPP
#define VIDEO_BUFFER_HPP

#include <array>
#include <cstdint>

namespace chip8
{
    class Video
    {
    public:
        std::array<std::uint32_t, 64* 32> videoBuffer = {0};
    };
}

#endif