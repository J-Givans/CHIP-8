#ifndef VIDEO_BUFFER_HPP
#define VIDEO_BUFFER_HPP

#include "Registers.hpp"
#include "Memory.hpp"

#include <array>
#include <cstdint>
#include <gsl/assert>

namespace chip8
{
    inline constexpr unsigned int VideoWidth = 64;
    inline constexpr unsigned int VideoHeight = 32;

    class Video
    {
    public:
        /// \brief Default constructor
        constexpr Video() noexcept = default;

        /// \brief Get the value in the video buffer at the given index
        /// \param[in] idx An index into the video buffer
        /// \returns The value in the video buffer at the given index
        constexpr uint32_t& operator[](size_t idx) noexcept;

        /// \brief Set the entire video buffer to zeros
        constexpr void clear() noexcept;

    private:
        std::array<std::uint32_t, VideoWidth * VideoHeight> videoBuffer = {0};
    };

    constexpr uint32_t& Video::operator[](size_t idx) noexcept
    {
        Expects(idx >= 0 and idx < videoBuffer.size() and "Index out of bounds");
        return videoBuffer[idx];
    }

    constexpr void Video::clear() noexcept
    {
        videoBuffer.fill(0);
    }
}

#endif