#pragma once

#include <array>
#include <unordered_map>

#include <SFML/Graphics.hpp>

namespace Cookie8
{
class Chip8;
class Keypad
{
    using Key = sf::Keyboard::Key;

  private:
    Chip8 &chip8;
    std::unordered_map<sf::Keyboard::Key, uint32_t> keymap{
        {Key::Num1, 0x1}, {Key::Num2, 0x2}, {Key::Num3, 0x3}, {Key::Num4, 0xC}, {Key::Q, 0x4}, {Key::W, 0x5},
        {Key::E, 0x6},    {Key::R, 0xD},    {Key::A, 0x7},    {Key::S, 0x8},    {Key::D, 0x9}, {Key::F, 0xE},
        {Key::Z, 0xA},    {Key::X, 0x0},    {Key::C, 0xB},    {Key::V, 0xF},
    };
    std::array<bool, 0x10> keys = {0};

  public:
    Keypad(Chip8 &chip8);
    void UpdateKey(Key key, bool state);
    bool GetKey(uint32_t key);
};
}; // namespace Cookie8