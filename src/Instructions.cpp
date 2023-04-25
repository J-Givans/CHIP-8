#include "Instructions.hpp"
#include "Memory.hpp"
#include "Video.hpp"
#include "Keypad.hpp"

#include <cstdint>

namespace chip8
{
    void op1nnn(Registers& reg) noexcept
    {
        reg.op1nnn();
    }

    void op3xkk(Registers& reg) noexcept
    {
        reg.op3xkk();
    }

    void op4xkk(Registers& reg) noexcept
    {
        reg.op4xkk();
    }

    void op5xy0(Registers& reg) noexcept
    {
        reg.op5xy0();
    }

    void op6xkk(Registers& reg) noexcept
    {
        reg.op6xkk();
    }

    void op7xkk(Registers& reg) noexcept
    {
        reg.op7xkk();
    }

    void op8xy0(Registers& reg) noexcept
    {
        reg.op8xy0();
    }

    void op8xy1(Registers& reg) noexcept
    {
        reg.op8xy1();
    }

    void op8xy2(Registers& reg) noexcept
    {
        reg.op8xy2();
    }

    void op8xy3(Registers& reg) noexcept
    {
        reg.op8xy3();
    }

    void op8xy4(Registers& reg) noexcept
    {
        reg.op8xy4();
    }

    void op8xy5(Registers& reg) noexcept
    {
        reg.op8xy5();
    }

    void op8xy6(Registers& reg) noexcept
    {
        reg.op8xy6();
    }

    void op8xy7(Registers& reg) noexcept
    {
        reg.op8xy7();
    }

    void op8xyE(Registers& reg) noexcept
    {
        reg.op8xyE();
    }

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