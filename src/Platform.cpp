#include "Platform.hpp"

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/System/Vector2.hpp>

namespace chip8
{
    Platform::Platform(std::string const& title, unsigned windowWidth, unsigned windowHeight)
    : window_(sf::VideoMode(windowWidth, windowHeight), title)
    {
    }

    void Platform::processInput(std::array<uint8_t, 16>& keys)
    {
        while (window_.isOpen()) {
            sf::Event event;
            using sf::Keyboard;

            while (window_.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window_.close();
                }
                else if (event.type == sf::Event::KeyPressed) {
                    if (Keyboard::isKeyPressed(Keyboard::Escape)) {
                        window_.close();
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::X)) {
                        keys[0] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num1)) {
                        keys[1] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                        keys[2] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                        keys[3] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Q)) {
                        keys[4] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::W)) {
                        keys[5] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::E)) {
                        keys[6] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::A)) {
                        keys[7] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::S)) {
                        keys[8] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::D)) {
                        keys[9] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Z)) {
                        keys[0xA] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::C)) {
                        keys[0xB] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                        keys[0xC] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::R)) {
                        keys[0xD] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::F)) {
                        keys[0xE] = 1;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::V)) {
                        keys[0xF] = 1;
                    }
                }
                else if (event.type == sf::Event::KeyReleased) {
                    if (Keyboard::isKeyPressed(Keyboard::X)) {
                        keys[0] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num1)) {
                        keys[1] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num2)) {
                        keys[2] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num3)) {
                        keys[3] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Q)) {
                        keys[4] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::W)) {
                        keys[5] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::E)) {
                        keys[6] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::A)) {
                        keys[7] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::S)) {
                        keys[8] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::D)) {
                        keys[9] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Z)) {
                        keys[0xA] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::C)) {
                        keys[0xB] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::Num4)) {
                        keys[0xC] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::R)) {
                        keys[0xD] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::F)) {
                        keys[0xE] = 0;
                    }
                    else if (Keyboard::isKeyPressed(Keyboard::V)) {
                        keys[0xF] = 0;
                    }
                }
            }
        }
    }
}