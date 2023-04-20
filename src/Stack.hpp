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

        /// \brief Remove the top element from the stack
        void pop();

        /// \brief Get the element at the top of the stack
        /// \returns A const reference to the most-recently pushed element
        std::uint16_t const& top() const;

        /// \brief Get the element at the top of the stack
        /// \returns A reference to the most-recently pushed element
        std::uint16_t& top();
    };
}

#endif