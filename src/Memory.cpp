#include "Memory.hpp"

#include <fstream>
#include <iterator>
#include <string>

namespace chip8
{
    void Memory::loadRom(char const* filename)
    {
        auto infile = std::ifstream(filename, std::ios::binary | std::ios::ate);

        if (!infile) {
            return;
        }

        std::streampos const size = infile.tellg();
        infile.seekg(0);
        
        std::string buffer;

        if (size < 0) {
            return;
        }

        buffer.reserve(static_cast<std::string::size_type>(size));
        buffer.assign(std::istreambuf_iterator<char>(infile.rdbuf()), std::istreambuf_iterator<char>());

        // Load the ROM contents into memory, starting at address 0x200
        std::copy(buffer.cbegin(), buffer.cend(), m_memory.begin() + StartAddress);

        Ensures(std::equal(buffer.cbegin(), buffer.cend(), m_memory.cbegin() + StartAddress));
    }
}