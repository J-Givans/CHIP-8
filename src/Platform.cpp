#include "Platform.hpp"

#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>

namespace chip8
{
    Platform::Platform(std::string const& title, unsigned windowWidth, unsigned windowHeight)
    : window_(sf::VideoMode(windowWidth, windowHeight), title)
    {
    }
}