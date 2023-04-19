#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <cstdint>

#include "FontSet.hpp"

namespace chip8
{
    inline constexpr unsigned int FontSetStartAddress = 0x50;

    class Memory
    {
    public:
        /// \brief Default constructor
        constexpr Memory() noexcept;

        /// \brief Load the font set into the memory buffer
        constexpr void loadFontSet() noexcept;

    private:
        std::array<std::uint8_t, 1024 * 4> m_memory = {0};
    };

    constexpr Memory::Memory() noexcept
    {
        loadFontSet();
    }

    constexpr void Memory::loadFontSet() noexcept
    {
        for (std::size_t i = 0; i < FontSetSize; ++i) {
            m_memory[FontSetStartAddress + i] = FontSet[i];
        }
    }
}

#endif