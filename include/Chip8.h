#pragma once

#include <array>
#include <cstdint>

using u8 = std::uint8_t;
using u16 = std::uint16_t;

namespace Cookie8
{
class Chip8
{
  private:
    // Memory
    std::array<u8, 0x1000> RAM = {0};
    std::array<u16, 0x10> stack = {0};

    // Registers
    std::array<u8, 0x10> V = {0};
    u16 PC = 0x0000;
    u16 I = 0x0000;
    u8 SP = 0x00;
    u8 delayTimer = 0x00;
    u8 soundTimer = 0x00;

  public:
    Chip8();
};
} // namespace Cookie8