#include "Application.h"

using namespace Cookie8;

Application::Application() : window{sf::VideoMode(WIDTH, HEIGHT), "SFML works!"}, chip8{}
{
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
}