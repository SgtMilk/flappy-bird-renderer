#include "window.h"
#include "SFML/Window.hpp"
#include <stdlib.h>
#include <unistd.h>

const int Window::NUM_PIPES = 4;
const int Window::PIPE_OFFSET_RANGE = 300;
const sf::Time Window::LOGIC_DT = sf::seconds(1.0 / 120);

Window::Window(int InScreenWidth, int InScreenHeight)
    : bird(sf::Vector2f(InScreenWidth / 2, InScreenHeight / 2))
{
    if(bird.getIsError()) return;

    for(int i = 0 ; i < NUM_PIPES ; i++) {
        Pipe pipe(InScreenWidth, InScreenHeight, i);
        if(pipe.getIsError()) return;

        pipes.push_back(pipe);
    }

    window.create(sf::VideoMode(InScreenWidth, InScreenHeight), "Flappy Bird");
}

void Window::run()
{   
    sf::Clock clk;

    sf::Time accumulator = sf::seconds(0);

    while(window.isOpen())
    {
        sf::Time frameTime = clk.getElapsedTime();
        clk.restart();

        accumulator += frameTime;

        while(accumulator >= LOGIC_DT)
        {
            handleEvents();
            update(LOGIC_DT.asSeconds());

            accumulator -= LOGIC_DT;
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