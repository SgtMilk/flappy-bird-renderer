#include "window.h"
#include "SFML/Window.hpp"

const int Window::NUM_PIPES = 4;
const int Window::PIPE_OFFSET_RANGE = 300;

Window::Window(int InScreenWidth, int InScreenHeight, int InFrameRate)
    : bird(sf::Vector2f(InScreenWidth / 2, InScreenHeight / 2), InFrameRate)
{
    if(bird.getIsError()) return;

    for(int i = 0 ; i < NUM_PIPES ; i++) {
        Pipe pipe(InScreenWidth, InScreenHeight, InFrameRate, i);
        if(pipe.getIsError()) return;

        pipes.push_back(pipe);
    }

    window.create(sf::VideoMode(InScreenWidth, InScreenHeight), "Flappy Bird");

    frameRate = InFrameRate;
    frameTime = sf::seconds(1.0f / frameRate);
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
            bird.jump();
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

    
    sf::Sprite birdSprite = bird.updatePosition();
    window.draw(birdSprite);

    float random_offset = rand() % PIPE_OFFSET_RANGE - PIPE_OFFSET_RANGE / 2.0f;
    for(int i = 0 ; i < NUM_PIPES ; i++) 
    {
        sf::Sprite pipeSprite = pipes[i].updatePosition(random_offset);
        window.draw(pipeSprite);
    }

    // resetting if bird touches pipe or falls too low
    bool isCollision = bird.checkCollision(pipes);
    bool ooo = bird.isOOO(window.getSize().y);
    if(isCollision || ooo) reset();

    // end the current frame
    window.display();
}

void Window::reset()
{
    for(int i = 0 ; i < NUM_PIPES ; i++) pipes[i].reset();
    bird.reset(window.getView().getCenter());
}