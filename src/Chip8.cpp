#include "Chip8.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <vector>

using namespace Cookie8;

Chip8::Chip8()
{
    // Load the font into RAM
    for (size_t i = 0x050; i <= 0x09F; i++)
    {
        RAM[i] = font[i - 0x050];
    }
}

u16 Chip8::Fetch()
{
    u8 hi = RAM[PC++];
    u8 lo = RAM[PC++];
    PC &= 0xFFF;

    return ((u16)hi << 8) | (u16)lo;
}

u16 Chip8::Decode(u16 instruction)
{
    // TODO: Implement Decode
    return 0;
}

void Chip8::Execute(u16 opcode)
{
    // TODO: Implement Execute
}

void Chip8::LoadProgram(std::string filepath)
{
    std::basic_ifstream<char> file{filepath, std::ios::binary};
    std::vector<u8> program = {std::istreambuf_iterator<char>{file}, {}};

    for (size_t i = 0; i < program.size(); i++)
    {
        RAM.at(i + 0x200) = program[i];
    }
}

void Chip8::Step()
{
    // TODO: Implement Step
}