#pragma once

#include <SFML/Graphics.hpp>

#include "Chip8.h"

namespace Cookie8
{
class Application
{
  private:
    static const unsigned int WIDTH = 64 * 5;
    static const unsigned int HEIGHT = 32 * 5;

    sf::RenderWindow window;
    Chip8 chip8;

  public:
    Application();
    void Run();
};
} // namespace Cookie8