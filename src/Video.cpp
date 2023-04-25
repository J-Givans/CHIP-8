#include "Video.hpp"

namespace chip8
{
    void Video::clear() noexcept
    {
        videoBuffer.fill(0);
    }
}