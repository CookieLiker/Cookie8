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

Chip8::InstructionInfo Chip8::Decode(u16 instruction)
{
    InstructionInfo instructionInfo{
        0x0000,
        (u16)(instruction & 0xFFF),
        (u16)(instruction & 0xF),
        (u16)(instruction & 0x0F00),
        (u16)(instruction & 0x00F0),
        (u16)(instruction & 0x00FF),
    };

    // TODO: Implement Decode
    switch (instruction & 0xF000)
    {
    case 0x0000:
        instructionInfo.opcode = instruction;
        break;

    case 0x8000:
        instructionInfo.opcode = instruction & 0xF00F;
        break;

    case 0xE000:
    case 0xF000:
        instructionInfo.opcode = instruction & 0xF0FF;
        break;

    default:
        instructionInfo.opcode = instruction & 0xF000;
        break;
    }

    return instructionInfo;
}

void Chip8::Execute(const InstructionInfo &instructionInfo)
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