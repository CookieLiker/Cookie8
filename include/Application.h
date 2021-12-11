#pragma once

#include <SFML/Graphics.hpp>

namespace Cookie8
{
class Application
{
  private:
    static const unsigned int WIDTH = 64 * 5;
    static const unsigned int HEIGHT = 32 * 5;

    sf::RenderWindow window;

  public:
    Application();
    void Run();
};
} // namespace Cookie8