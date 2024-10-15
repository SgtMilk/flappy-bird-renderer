#include "window.h"
#include "SFML/Window.hpp"
#include <stdlib.h>
#include <unistd.h>

const int Window::NUM_PIPES = 4;
const int Window::PIPE_OFFSET_RANGE = 300;

Window::Window(int InScreenWidth, int InScreenHeight, int InFrameRate)
    : bird(sf::Vector2f(InScreenWidth / 2, InScreenHeight / 2))
{
    if(bird.getIsError()) return;

    for(int i = 0 ; i < NUM_PIPES ; i++) {
        Pipe pipe(InScreenWidth, InScreenHeight, i);
        if(pipe.getIsError()) return;

        pipes.push_back(pipe);
    }

    window.create(sf::VideoMode(InScreenWidth, InScreenHeight), "Flappy Bird");

    frameRate = InFrameRate;
    frameTime = sf::seconds(1.0f / frameRate);
}

void Window::run()
{   
    const sf::Time dt = sf::seconds(1.0 / frameRate);
    sf::Clock clk;

    while(window.isOpen())
    {
        sf::Time frameTime = clk.getElapsedTime();
        clk.restart();

        while(frameTime > sf::seconds(0))
        {
            sf::Time deltaTime = frameTime < dt ? frameTime : dt;

            handleEvents();
            update(deltaTime.asSeconds());

            frameTime -= deltaTime;;
        }
        render();
    }
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

void Window::update(float dt)
{
    bird.updatePosition(dt);

    float random_offset = rand() % PIPE_OFFSET_RANGE - PIPE_OFFSET_RANGE / 2.0f;
    for(int i = 0 ; i < NUM_PIPES ; i++) pipes[i].updatePosition(dt, random_offset);

    // resetting if bird touches pipe or falls too low
    bool isCollision = bird.checkCollision(pipes);
    bool ooo = bird.isOOO(window.getSize().y);
    if(isCollision || ooo) reset();
}

void Window::render()
{
    window.clear(sf::Color::Cyan);

    window.draw(bird.sprite);
    for(int i = 0 ; i < NUM_PIPES ; i++) window.draw(pipes[i].sprite);

    window.display();
}

void Window::reset()
{
    for(int i = 0 ; i < NUM_PIPES ; i++) pipes[i].reset();
    bird.reset(window.getView().getCenter());
}