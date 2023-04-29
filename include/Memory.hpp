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
    constexpr void loadFontSet(std::array<uint8_t, size>& memoryBuffer, uint8_t const from) noexcept
    {
        Expects(memoryBuffer.size() >= FontSetSize and "Buffer capacity cannot accomodate font set");

        std::size_t i {0};
        
        for (auto const& font : FontSet) {
            memoryBuffer[from + i] = font;
            ++i;
        }

        Ensures(std::equal(FontSet.cbegin(), FontSet.cend(), memoryBuffer.cbegin() + from));
    }

    class Memory
    {
    public:
        /// \brief Default constructor
        constexpr Memory() noexcept;

        /// \brief Get the value in the memory location referenced by the given index
        /// \param[in] index The index into the memory block
        /// \returns The value in the memory location at index
        constexpr uint8_t& operator[](uint16_t index) noexcept;
        
        /// \brief Get the value in the memory location referenced by the given index
        /// \param[in] index The index into the memory block
        /// \returns The value in the memory location at index
        constexpr uint8_t operator[](uint16_t index) const noexcept;

        /// \brief Returns an iterator to the first element in the memory buffer
        constexpr auto begin() noexcept;
        
        /// \brief Returns a const-iterator to the first element in the memory buffer
        constexpr auto cbegin() const noexcept;

        /// \brief Returns an iterator to the first element past the end of the memory buffer
        constexpr auto end() noexcept;
        
        /// \brief Returns a const-iterator to the first element past the end of the memory buffer
        constexpr auto cend() const noexcept;

        /// \brief Load the font set into the memory buffer
        constexpr void loadFontSet() noexcept;

        /// \brief Load a ROM into the memory buffer
        /// \param[in] filename The path to the ROM file
        void loadRom(char const* filename);
    
    private:
        std::array<std::uint8_t, 1024 * 4> m_memory = {0};
    };

    constexpr Memory::Memory() noexcept
    {
        loadFontSet();
    }

    constexpr uint8_t& Memory::operator[](uint16_t index) noexcept
    {
        Expects(index >= 0 and index < m_memory.size());
        return m_memory[index];
    }

    constexpr uint8_t Memory::operator[](uint16_t index) const noexcept
    {
        Expects(index >= 0 and index < m_memory.size());
        return m_memory[index];
    }

    constexpr void Memory::loadFontSet() noexcept
    {
        chip8::loadFontSet(m_memory, FontSetStartAddress);
    }

    constexpr auto Memory::begin() noexcept
    {
        return m_memory.begin();
    }

    constexpr auto Memory::cbegin() const noexcept
    {
        return m_memory.cbegin();
    }

    constexpr auto Memory::end() noexcept
    {
        return m_memory.end();
    }

    constexpr auto Memory::cend() const noexcept
    {
        return m_memory.cend();
    }
}

#endif