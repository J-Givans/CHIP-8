#include "Stack.hpp"

namespace chip8
{
    void Stack::pop()
    {
        stack.pop();
    }

    std::uint16_t const& Stack::top() const
    {
        return stack.top();
    }

    std::uint16_t& Stack::top()
    {
        return stack.top();
    }

    void Stack::push(std::uint16_t value)
    {
        stack.push(value);
    }
}