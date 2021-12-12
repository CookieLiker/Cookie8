#include "Application.h"

using namespace Cookie8;

Application::Application() : window{sf::VideoMode(WIDTH, HEIGHT), "SFML works!"}
{
    window.setFramerateLimit(60);
}

void Application::Run()
{
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
                window.close();
                break;

            default:
                break;
            }
        }
    }

    for (size_t i = 0; i < 12; i++)
    {
        chip8.Step();
    }
}