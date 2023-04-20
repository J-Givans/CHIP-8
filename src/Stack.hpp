#ifndef STACK_HPP
#define STACK_HPP

#include <stack>
#include <array>
#include <cstdint>

namespace chip8
{
    class Stack
    {
    public:
        std::stack<std::uint16_t, std::array<std::uint16_t, 16>> stack {};

        Stack() noexcept = default;
    };
}

#endif