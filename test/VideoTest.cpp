#include "Video.hpp"

#include <gtest/gtest.h>
#include <gmock/gmock.h>

class VideoTest : public ::testing::Test
{
public:
    chip8::Video video_;
};

TEST_F(VideoTest, IsClearedWhenCreated)
{
    using chip8::VideoWidth;
    using chip8::VideoHeight;

    for (auto i = 0u; i < VideoWidth * VideoHeight; ++i) {
        ASSERT_THAT(video_[i], ::testing::Eq(0));
    }
}