#include "Chip8.h"

#include <iostream>

using namespace Cookie8;

Chip8::Chip8()
{
    // Load the font into RAM
    for (size_t i = 0x050; i <= 0x09F; i++)
    {
        RAM[i] = font[i - 0x050];
    }
}