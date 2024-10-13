#pragma once

#include <SFML/Graphics.hpp>

#include "bird.h"
#include "pipes.h"

class Window
{
public:
    Window(int screenWidth, int screenHeight, int frameRate);

    void handleEvents();
    bool isOpen();

    void update();
    void reset();
private:
    sf::RenderWindow window;

    float frameRate;
    sf::Time frameTime;
    sf::Clock clk;

    Bird bird;
    Pipes pipes;
};