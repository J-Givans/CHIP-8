#include "Memory.hpp"
#include "FontSet.hpp"

#include <gtest/gtest.h>

#include <algorithm>
#include <array>

using namespace chip8;

TEST(LoadFontSetTest, LoadsFontSetIntoMemoryBuffer)
{
    std::array<uint8_t, FontSetSize> buffer;
    loadFontSet(buffer, 0);
    
    ASSERT_TRUE(std::equal(buffer.cbegin(), buffer.cend(), FontSet.cbegin()));
}

class AMemoryTest : public ::testing::Test
{
public:
    Memory memory;
};

TEST_F(AMemoryTest, ContainsFontSetAtInstantiation)
{
    ASSERT_TRUE(std::equal(FontSet.cbegin(), FontSet.cend(), memory.cbegin() + FontSetStartAddress));
}