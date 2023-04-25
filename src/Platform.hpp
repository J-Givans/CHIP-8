#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics/RenderWindow.hpp>

#include <cstdint>
#include <string>

namespace chip8
{
    class Platform
    {
    public:
        /// \brief Default constructor
        /// \details Create a new render window with the given dimensions and title
        /// \param[in] title The title of the window
        /// \param[in] windowWidth, windowHeight The dimensions of the window
        Platform(std::string const& title, unsigned windowWidth, unsigned windowHeight);

    private:
        sf::RenderWindow window_;
    };
}

#endif