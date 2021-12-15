#include "Application.h"

#include <filesystem>
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

    if (!std::filesystem::exists(args[1]))
    {
        std::cout << "Not a valid filepath" << std::endl;
        exit(0);
    }

    const auto &s = args[2];
    bool isAValidSpeed =
        !s.empty() && std::find_if(s.begin(), s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();

    if (!isAValidSpeed)
    {
        std::cout << "Not a valid speed" << std::endl;
        exit(0);
    }

    chip8.LoadProgram(args[1]);
    chip8.speed = stoi(args[2]);
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