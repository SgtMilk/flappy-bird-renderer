#include "pipes.h"
#include "SFML/Window.hpp"

#include <iostream>

Pipes::Pipes(int screenWidth, int screenHeight, int frameRate)
{
    bool res = pipeTexture.loadFromFile("./lib/pipe.png");
    if(!res) std::cout << "Cannot load pipe\n";

    pipeSprites = new sf::Sprite[NUM_PIPES];
    if (pipeSprites == nullptr) std::cout << "Pipe array could not be created\n";

    for(int i = 0 ; i < NUM_PIPES ; i++)
    {
        this->pipeSprites[i].setTexture(pipeTexture, true);
        this->pipeSprites[i].setScale(PIPE_SCALE, PIPE_SCALE);

        if(i % 2 == 1) this->pipeSprites[i].setRotation(180);

        sf::Vector2f dimensions = this->pipeSprites[i].getLocalBounds().getSize();
        this->pipeSprites[i].setOrigin(dimensions.x / 2, dimensions.y / 2);

        sf::Vector2f position;
        bool isFirstPipe = int(i / 2) == 0;
        position.x = screenWidth * (isFirstPipe ? 3 : 1) / 4 + int(isFirstPipe) * dimensions.x / 2;
        position.y = screenHeight * (i % 2 == 0 ? 6 : 0) / 6;
        
        this->pipeSprites[i].setPosition(position);
    }

    this->frameRate = frameRate;
    this->speed = 500.0f / frameRate;
    this->screenWidth = screenWidth;
    this->screenHeight = screenHeight;
}

Pipes::~Pipes()
{
    delete pipeSprites;
}

sf::Sprite *Pipes::updatePosition()
{
    float halfWidth = pipeSprites[0].getLocalBounds().getSize().x / 2;

    float rand_cache = -PIPE_OFFSET_RANGE;
    for(int i = 0 ; i < NUM_PIPES ; i++)
    {
        sf::Vector2f pos = this->pipeSprites[i].getPosition();
        pos.x -= this->speed;
        if(pos.x < -1 * halfWidth) 
        {
            pos.x = this->screenWidth + halfWidth;

            if(rand_cache == -PIPE_OFFSET_RANGE) rand_cache = rand() % PIPE_OFFSET_RANGE - PIPE_OFFSET_RANGE / 2.0f;
            pos.y = this->screenHeight * (i % 2 == 0 ? 6 : 0) / 6 + rand_cache;
            
        }
        this->pipeSprites[i].setPosition(pos);
    }

    return pipeSprites;
}