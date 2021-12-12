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
        opcode : 0x0000,
        nnn : (u16)(instruction & 0xFFF),
        n : (u16)(instruction & 0xF),
        x : (u16)((instruction & 0x0F00) >> 8),
        y : (u16)((instruction & 0x00F0) >> 4),
        kk : (u16)(instruction & 0x00FF),
    };

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
    switch (instructionInfo.opcode)
    {
    case 0x00E0:
        display.Clear();
        break;
    case 0x1000:
        PC = instructionInfo.nnn;
        break;
    case 0x6000:
        V[instructionInfo.x] = (u8)instructionInfo.kk;
        break;
    case 0x7000:
        V[instructionInfo.x] += (u8)instructionInfo.kk;
        break;
    case 0xA000:
        I = instructionInfo.nnn;
        break;
    case 0xD000:
        DRW(instructionInfo.x, instructionInfo.y, instructionInfo.n);
        break;
    }
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
    for (size_t i = 0; i < speed / 60; i++)
    {
        auto e = Decode(Fetch());
        Execute(e);
    }
}

Display &Chip8::GetDisplay()
{
    return display;
}

void Chip8::DRW(u16 x, u16 y, u16 n)
{
    V[0xF] = 0;
    auto xCoord = V[x];
    auto yCoord = V[y];

    for (int r = 0; r < n; r++)
    {
        auto spriteStrip = RAM[I + r];

        for (int c = 0; c < 8; c++)
        {
            auto pixelCoord = sf::Vector2u((xCoord + c) & 0x3F, (yCoord + r) & 0x1F);
            auto currentPixel = display.GetPixel(pixelCoord);
            auto spritePixel = (spriteStrip & 0x80) != 0;
            auto newPixel = currentPixel != spritePixel;

            if (currentPixel && !newPixel)
            {
                V[0xF] = 1;
            }

            display.SetPixel(pixelCoord, newPixel);
            spriteStrip <<= 1;
        }
    }
}