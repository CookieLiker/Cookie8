#pragma once

#include <array>

#include <SFML/Graphics.hpp>

namespace Cookie8
{
class Display
{
  private:
    static const unsigned int WIDTH = 64;
    static const unsigned int HEIGHT = 32;
    std::array<bool, WIDTH *HEIGHT> data = {0};
    sf::Color framebuffer[WIDTH * HEIGHT];
    sf::Texture framebufferTexture;

  public:
    Display();
    void Clear();
    void SetPixel(sf::Vector2u coord, bool pixel);
    bool GetPixel(sf::Vector2u coord);
    const sf::Texture &RegenerateTexture();
};
} // namespace Cookie8