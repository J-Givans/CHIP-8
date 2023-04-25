#include "Instructions.hpp"
#include "Memory.hpp"
#include "Video.hpp"
#include "Keypad.hpp"

#include <cstdint>

namespace chip8
{
    void op9xy0(Registers& reg) noexcept
    {
        reg.op9xy0();
    }

    void opAnnn(Registers& reg) noexcept
    {
        reg.opAnnn();
    }

    void opBnnn(Registers& reg) noexcept
    {
        reg.opBnnn();
    }

    void opCxkk(Registers& reg) noexcept
    {
        reg.opCxkk();
    }

    void opEx9E(Registers& reg) noexcept
    {
        reg.opEx9E();
    }

    void opExA1(Registers& reg) noexcept
    {
        reg.opExA1();
    }

    void opFx0A(Registers& reg) noexcept
    {
        reg.opFx0A();
    }

    void opFx1E(Registers& reg) noexcept
    {
        reg.opFx1E();
    }

    void opFx29(Registers& reg) noexcept
    {
        reg.opFx29();
    }
}