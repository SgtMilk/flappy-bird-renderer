#include "window.h"
#include "SFML/Window.hpp"

Window::Window(int screenWidth, int screenHeight, int frameRate) 
{
    window.create(sf::VideoMode(screenWidth, screenHeight), "Flappy Bird");

    sf::Vector2u windowDimensions = window.getSize();
    pipes = new Pipes(windowDimensions.x, window.getSize().y, frameRate);

    sf::Vector2f center = window.getView().getCenter();
    bird = new Bird(center, frameRate);

    this->frameRate = frameRate;
    this->frameTime = sf::seconds(1.0f / frameRate);
}

void Window::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            window.close();
            return;
        }

        if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
        {
            bird->jump();
            return;
        }

    }
}

bool Window::isOpen()
{
    return window.isOpen();
}

void Window::update()
{
    // check if timing is right
    if(clk.getElapsedTime() < frameTime) return;

    clk.restart();

    // clear the window with cyan color
    window.clear(sf::Color::Cyan);

    sf::Sprite* pipeSprites = pipes->updatePosition();
    sf::Sprite birdSprite = bird->updatePosition();

    for(int i = 0 ; i < pipes->NUM_PIPES ; i++) window.draw(pipeSprites[i]);
    window.draw(birdSprite);

    // resetting if bird touches pipe or falls too low
    bool isCollision = bird->checkCollision(pipeSprites, pipes->NUM_PIPES);
    bool ooo = bird->isOOO(window.getSize().y);
    if(isCollision || ooo) reset();

    // end the current frame
    window.display();
}

void Window::reset()
{
    pipes = new Pipes(window.getSize().x, window.getSize().y, frameRate);
    sf::Vector2f center = window.getView().getCenter();
    bird = new Bird(center, frameRate);
}