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
    PC &= 0xFFF;
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

void Chip8::Execute(const InstructionInfo &ii)
{
    switch (ii.opcode)
    {
    case 0x00E0:
        display.Clear();
        break;
    case 0x1000:
        PC = ii.nnn;
        break;
    case 0x6000:
        V[ii.x] = (u8)ii.kk;
        break;
    case 0x7000:
        V[ii.x] += (u8)ii.kk;
        break;
    case 0xA000:
        I = ii.nnn;
        break;
    case 0xD000:
        DRW(ii.x, ii.y, ii.n);
        break;
    case 0x3000:
        if (V[ii.x] == ii.kk)
        {
            PC += 2;
        }
        break;
    case 0x4000:
        if (V[ii.x] != ii.kk)
        {
            PC += 2;
        }
        break;
    case 0x2000:
        stack[++SP] = PC;
        PC = ii.nnn;
        break;
    case 0xC000:
        V[ii.x] = (rand() % 256) & ii.kk;
        break;
    case 0x5000:
        if (V[ii.x] == V[ii.y])
        {
            PC += 2;
        }
        break;
    case 0x8005:
        SUB(V[ii.x], V[ii.y], ii.x);
        break;

    case 0x8007:
        SUB(V[ii.y], V[ii.x], ii.x);
        break;

    case 0x8001:
        V[ii.x] = V[ii.x] | V[ii.y];
        break;

    case 0x8002:
        V[ii.x] = V[ii.x] & V[ii.y];
        break;

    case 0x8003:
        V[ii.x] = V[ii.x] ^ V[ii.y];
        break;

    case 0x800E:
        V[0xF] = V[ii.x] >> 7;
        V[ii.x] <<= 1;
        break;

    case 0x8006:
        V[0xF] = V[ii.x] & 1;
        V[ii.x] >>= 1;
        break;

    case 0xF055:
        for (unsigned int i = 0; i <= ii.x; i++)
        {
            RAM[I + i] = V[i];
        }
        break;

    case 0xF065:
        for (unsigned int i = 0; i <= ii.x; i++)
        {
            V[i] = RAM[I + i];
        }
        break;

    case 0xF033:
        RAM[I] = V[ii.x] / 100;
        RAM[I + 1] = (V[ii.x] % 100) / 10;
        RAM[I + 2] = V[ii.x] % 10;
        break;

    case 0xF01E:
        I += V[ii.x];
        break;

    default:
        std::cout << "Not implemented opcode: " << std::hex << ii.opcode << "\n";
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

void Chip8::ADD(u16 x, u16 y)
{
    u16 result = (u16)V[x] + (u16)V[y];
    V[x] = result & 0xFF;
    V[0xF] = result > 255;
}

void Chip8::SUB(u8 op1, u8 op2, u16 x)
{
    V[0xF] = op1 > op2;
    V[x] = op1 - op2;
}