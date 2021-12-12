#include "Display.h"

using namespace Cookie8;

Display::Display()
{
    framebufferTexture.create(WIDTH, HEIGHT);
}

void Display::Clear()
{
    data.fill(false);
}

void Display::SetPixel(sf::Vector2u coord, bool pixel)
{
    data[coord.x + coord.y * WIDTH] = pixel;
}

bool Display::GetPixel(sf::Vector2u coord)
{
    return data[coord.x + coord.y * WIDTH];
}

const sf::Texture &Display::RegenerateTexture()
{
    for (uint32_t y = 0; y < HEIGHT; y++)
    {
        for (uint32_t x = 0; x < WIDTH; x++)
        {
            framebuffer[x + y * WIDTH] = data[x + y * WIDTH] ? sf::Color::White : sf::Color::Black;
        }
    }

    framebufferTexture.update((sf::Uint8 *)framebuffer);
    return framebufferTexture;
}
