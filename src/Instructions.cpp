#include "Instructions.hpp"
#include "Memory.hpp"
#include "Video.hpp"
#include "Keypad.hpp"

#include <cstdint>

namespace chip8
{
    constexpr void op00E0(Video& video) noexcept
    {
        video.clear();
    }

    void op00EE(Stack& stack, Registers& reg) noexcept
    {
        stack.pop();
        reg.setProgramCounter(stack.top());
    }

    void op1nnn(Registers& reg) noexcept
    {
        reg.op1nnn();
    }

    void op2nnn(Stack& stack, Registers& reg)
    {
        std::uint16_t address = opcode & 0x0FFFu;

        stack.push(reg.getProgramCounter());
        reg.setProgramCounter(address);
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

    void opDxyn(Video& video, Memory& memory, Registers& reg) noexcept
    {
        video.opDxyn(memory, reg);
    }

    void opEx9E(Registers& reg) noexcept
    {
        reg.opEx9E();
    }

    void opExA1(Registers& reg) noexcept
    {
        reg.opExA1();
    }

    void opFx07(Registers& reg, Timers const& timers) noexcept
    {
        reg.opFx07(timers);
    }

    void opFx0A(Registers& reg) noexcept
    {
        reg.opFx0A();
    }

    void opFx15(Registers const& reg, Timers& timers) noexcept
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        timers.delayTimer = reg[Vx];
    }

    void opFx18(Registers& reg, Timers& timers)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        timers.soundTimer = reg[Vx];
    }

    void opFx1E(Registers& reg) noexcept
    {
        reg.opFx1E();
    }

    void opFx29(Registers& reg) noexcept
    {
        reg.opFx29();
    }

    void opFx33(Memory& memory, Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;
        uint8_t value = reg[Vx];

        // 1s place
        memory.m_memory[reg.getIndexRegister() + 2] = value % 10;
        value /= 10;

        // 10s place
        memory.m_memory[reg.getIndexRegister() + 1] = value % 10;
        value /= 10;

        // 100s place
        memory.m_memory[reg.getIndexRegister()] = value % 10;
    }

    void opFx65(Memory const& memory, Registers& reg)
    {
        uint8_t Vx = (opcode & 0x0F00u) >> 8u;

        for (uint8_t i = 0; i <= Vx; ++i) {
            reg[i] = memory.m_memory[reg.getIndexRegister() + i];
        }
    }
}