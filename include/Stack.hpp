#ifndef STACK_HPP
#define STACK_HPP

#include <stack>
#include <vector>
#include <cstdint>

namespace chip8
{
    class Stack
    {
    public:
        std::stack<std::uint16_t, std::vector<std::uint16_t>> stack { std::vector<std::uint16_t>(16) };

        Stack() noexcept = default;

        /// \brief Remove the top element from the stack
        void pop();

        /// \brief Get the element at the top of the stack
        /// \returns A const reference to the most-recently pushed element
        std::uint16_t const& top() const;

        /// \brief Get the element at the top of the stack
        /// \returns A reference to the most-recently pushed element
        std::uint16_t& top();

        /// \brief Push an element to the top of the stack
        /// \param[in] value The element to be pushed to the top of the stack
        void push(std::uint16_t value);

        /// \brief Is the stack empty?
        /// \returns true If the stack is empty, false otherwise
        [[nodiscard]] constexpr bool isEmpty() const& noexcept;

        /// \brief Get the number of elements in the stack
        /// \returns The number of elements present in the stack
        [[nodiscard]] constexpr bool size() const& noexcept;
    };

    [[nodiscard]]
    constexpr bool Stack::isEmpty() const& noexcept
    {
        return stack.empty();
    }

    [[nodiscard]]
    constexpr bool Stack::size() const& noexcept
    {
        return stack.size();
    }
}

#endif