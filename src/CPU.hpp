#ifndef CPU_HPP
#define CPU_HPP

#include "Memory.hpp"
#include "Registers.hpp"
#include "Stack.hpp"
#include "Timers.hpp"
#include "Video.hpp"

namespace chip8
{
    class CPU
    {
    public:
        CPU() = default;

    private:
        Memory memory_;
        Registers registers_;
        Stack stack_;
        Timers timers_;
        Video video_;
    };
}

#endif