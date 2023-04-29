#include "Memory.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>

using namespace chip8;

TEST(LoadFontSetTest, LoadsFontSetIntoMemoryBuffer)
{
    std::array<uint8_t, 80> buffer;
    loadFontSet(buffer, 0);
    
    ASSERT_TRUE(std::equal(buffer.cbegin(), buffer.cend(), FontSet.cbegin()));
}