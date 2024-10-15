#pragma once

#include <SFML/Graphics.hpp>

#include "bird.h"
#include "pipe.h"

class Window
{
public:
    Window(int screenWidth, int screenHeight, int frameRate);

    void run();

    void handleEvents();

    void update(float dt);
    void render();

    void reset();
private:
    static const int NUM_PIPES;
    static const int PIPE_OFFSET_RANGE;

    sf::RenderWindow window;

    float frameRate;
    sf::Time frameTime;

    Bird bird;
    std::vector<Pipe> pipes;
    sf::Texture pipeTexture;
};