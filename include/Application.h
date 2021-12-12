#pragma once

#include <SFML/Graphics.hpp>

#include "Chip8.h"

namespace Cookie8
{
class Application
{
  private:
    static const unsigned int SCALE_FACTOR = 5;
    static const unsigned int WIDTH = 64 * SCALE_FACTOR;
    static const unsigned int HEIGHT = 32 * SCALE_FACTOR;

    sf::RenderWindow window;
    Chip8 chip8;
    sf::Sprite chip8Sprite;

  public:
    Application(int argc, char *argv[]);
    void ProcessArguments(int argc, char *argv[]);
    void Run();
};
} // namespace Cookie8