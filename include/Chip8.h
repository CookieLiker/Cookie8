#pragma once

#include <array>
#include <cstdint>
#include <string>

#include "Display.h"
#include "Keypad.h"

using u8 = std::uint8_t;
using u16 = std::uint16_t;

namespace Cookie8
{
class Chip8
{
  public:
    static const unsigned int WIDTH = 64;
    static const unsigned int HEIGHT = 32;

  private:
    // Memory
    std::array<u8, 0x1000> RAM = {0};
    std::array<u16, 0x10> stack = {0};

    // Registers
    std::array<u8, 0x10> V = {0};
    u16 PC = 0x200;
    u16 I = 0x0000;
    u8 SP = 0x00;
    u8 DT = 0x00;
    u8 ST = 0x00;

    // Display
    Display display;

    bool halted = false;
    uint32_t haltRegister = 0;

    // NumberSprites
    std::array<u8, 0x10 * 5> font{
        0xF0, 0x90, 0x90, 0x90, 0xF0, // 0
        0x20, 0x60, 0x20, 0x20, 0x70, // 1
        0xF0, 0x10, 0xF0, 0x80, 0xF0, // 2
        0xF0, 0x10, 0xF0, 0x10, 0xF0, // 3
        0x90, 0x90, 0xF0, 0x10, 0x10, // 4
        0xF0, 0x80, 0xF0, 0x10, 0xF0, // 5
        0xF0, 0x80, 0xF0, 0x90, 0xF0, // 6
        0xF0, 0x10, 0x20, 0x40, 0x40, // 7
        0xF0, 0x90, 0xF0, 0x90, 0xF0, // 8
        0xF0, 0x90, 0xF0, 0x10, 0xF0, // 9
        0xF0, 0x90, 0xF0, 0x90, 0x90, // A
        0xE0, 0x90, 0xE0, 0x90, 0xE0, // B
        0xF0, 0x80, 0x80, 0x80, 0xF0, // C
        0xE0, 0x90, 0x90, 0x90, 0xE0, // D
        0xF0, 0x80, 0xF0, 0x80, 0xF0, // E
        0xF0, 0x80, 0xF0, 0x80, 0x80  // F
    };

    struct InstructionInfo
    {
        u16 opcode;
        u16 nnn;
        u16 n;
        u16 x;
        u16 y;
        u16 kk;
    };

    u16 Fetch();
    InstructionInfo Decode(u16 instruction);
    void Execute(const InstructionInfo &instructionInfo);

    void DRW(u16 x, u16 y, u16 n);
    void ADD(u8 op1, u8 op2, u16 x);
    void SUB(u8 op1, u8 op2, u16 x);
    void SkipIf(bool condition);

  public:
    unsigned int speed = 0;

    // Keyboard
    Keypad keypad;

    Chip8();
    void LoadProgram(std::string filepath);
    void Step();
    bool IsHalted();
    void UnHalt(uint32_t key);
    Display &GetDisplay();
};
} // namespace Cookie8