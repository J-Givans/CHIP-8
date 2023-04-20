#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <array>
#include <cstdint>
#include <algorithm>

#include <gsl/assert>

#include "FontSet.hpp"

namespace chip8
{
    inline constexpr unsigned int StartAddress = 0x200;
    inline constexpr unsigned int FontSetStartAddress = 0x50;

    /// \brief Load the font set into the memory buffer
    /// \tparam size The size of the memory buffer
    /// \param[in] memoryBuffer The memory buffer
    template <std::size_t size>
    constexpr void loadFontSet(std::array<uint8_t, size>& memoryBuffer) noexcept
    {
        Expects(memoryBuffer.size() > FontSetSize);

        std::size_t i {0};
        
        for (auto const& font : FontSet) {
            memoryBuffer[FontSetStartAddress + i] = font;
            ++i;
        }

        Ensures(std::equal(FontSet.cbegin(), FontSet.cend(), memoryBuffer.cbegin() + FontSetStartAddress));
    }

    class Memory
    {
    public:
        std::array<std::uint8_t, 1024 * 4> m_memory = {0};

        /// \brief Default constructor
        constexpr Memory() noexcept;

        /// \brief Load the font set into the memory buffer
        constexpr void loadFontSet() noexcept;

        /// \brief Load a ROM into the memory buffer
        /// \param[in] filename The path to the ROM file
        void loadRom(char const* filename);
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