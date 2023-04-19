#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <cstdint>

#include <gsl/assert>

#include "FontSet.hpp"

namespace chip8
{
    inline constexpr unsigned int FontSetStartAddress = 0x50;

    /// \brief Load the font set into the memory buffer
    /// \tparam size The size of the memory buffer
    /// \param[in] memoryBuffer The memory buffer
    template <std::size_t size>
    constexpr void loadFontSet(std::array<uint8_t, size>& memoryBuffer) noexcept
    {
        Expects(memoryBuffer.size() > FontSetSize);

        for (std::size_t i = 0; i < FontSetSize; ++i) {
            memoryBuffer[FontSetStartAddress + i] = FontSet[i];
        }
    }

    class Memory
    {
    public:
        /// \brief Default constructor
        constexpr Memory() noexcept;

    private:
        std::array<std::uint8_t, 1024 * 4> m_memory = {0};

        /// \brief Load the font set into the memory buffer
        constexpr void loadFontSet() noexcept;
    };

    constexpr Memory::Memory() noexcept
    {
        loadFontSet();
    }

    constexpr void Memory::loadFontSet() noexcept
    {
        chip8::loadFontSet(m_memory);
    }
}

#endif