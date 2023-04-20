#include "Video.hpp"

#include <gtest/gtest.h>

#include <algorithm>

using chip8::Video;
using ::testing::Eq;

TEST(VideoTest, IsClearedWhenCreated)
{
    Video video;
    
    ASSERT_EQ(
        std::all_of(
            video.videoBuffer.cbegin(), 
            video.videoBuffer.cend(), 
            [](uint32_t val) { return val == 0; }), 
        Eq(0)
    );
}