#include "Keypad.h"

#include "Chip8.h"

using namespace Cookie8;

Keypad::Keypad(Chip8 &chip8) : chip8{chip8}
{
}

void Keypad::UpdateKey(sf::Keyboard::Key key, bool state)
{
    auto k = keymap[key];
    if (state && chip8.IsHalted())
    {
        chip8.UnHalt(k);
    }

    keys[k] = state;
}

bool Keypad::GetKey(uint32_t key)
{
    return keys.at(key);
}