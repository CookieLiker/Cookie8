#include "Application.h"

#include <iostream>

using namespace Cookie8;

Application::Application(int argc, char *argv[]) : window{sf::VideoMode(WIDTH, HEIGHT), "Cookie8"}
{
    chip8Sprite.setScale(sf::Vector2f(SCALE_FACTOR, SCALE_FACTOR));
    window.setFramerateLimit(60);
    ProcessArguments(argc, argv);
}

void Application::ProcessArguments(int argc, char *argv[])
{
    std::vector<std::string> args(argv, argv + argc);

    if (args.size() < 3)
    {
        std::cout << "Not enough arguements" << std::endl;
        exit(0);
    }

    chip8.LoadProgram(args[1]);
    chip8.speed = (unsigned int)stoi(args[2]);
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

            case sf::Event::KeyPressed:
                chip8.keypad.UpdateKey(event.key.code, true);
                break;

            case sf::Event::KeyReleased:
                chip8.keypad.UpdateKey(event.key.code, false);
                break;

            default:
                break;
            }
        }

        chip8.Step();
        chip8Sprite.setTexture(chip8.GetDisplay().RegenerateTexture());

        window.clear();
        window.draw(chip8Sprite);
        window.display();
    }
}