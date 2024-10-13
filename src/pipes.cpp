#include "pipes.h"

#include <iostream>

const int Pipes::NUM_PIPES = 4;
const float Pipes::PIPE_SCALE = 0.4;
const int Pipes::PIPE_OFFSET_RANGE = 300;
const float Pipes::SPEED_PER_SECOND = 500;

Pipes::Pipes(int InScreenWidth, int InScreenHeight, int InFrameRate)
{
    frameRate = InFrameRate;
    speed = SPEED_PER_SECOND / frameRate;
    screenWidth = InScreenWidth;
    screenHeight = InScreenHeight;

    bool res = pipeTexture.loadFromFile("./lib/pipe.png");
    if(!res) {
        std::cout << "Cannot load pipe image. Exiting.\n";
        isError = true;
        return;
    };

    for(int i = 0 ; i < NUM_PIPES ; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(pipeTexture, true);
        sprite.setScale(PIPE_SCALE, PIPE_SCALE);

        if(i % 2 == 1) sprite.setRotation(180);

        sf::Vector2f dimensions = sprite.getLocalBounds().getSize();
        sprite.setOrigin(dimensions.x / 2, dimensions.y / 2);

        pipeSprites.push_back(sprite);
    }

    reset();

    isError = false;
}

std::vector<sf::Sprite> Pipes::updatePosition()
{
    float halfWidth = pipeSprites[0].getLocalBounds().getSize().x / 2;

    float rand_cache = -PIPE_OFFSET_RANGE;
    for(int i = 0 ; i < NUM_PIPES ; i++)
    {
        sf::Vector2f pos = pipeSprites[i].getPosition();
        pos.x -= speed;
        if(pos.x < -1 * halfWidth) 
        {
            pos.x = screenWidth + halfWidth;

            if(rand_cache == -PIPE_OFFSET_RANGE) rand_cache = rand() % PIPE_OFFSET_RANGE - PIPE_OFFSET_RANGE / 2.0f;
            pos.y = screenHeight * (i % 2 == 0 ? 6 : 0) / 6 + rand_cache;
            
        }
        pipeSprites[i].setPosition(pos);
    }

    return pipeSprites;
}

void Pipes::reset()
{
    for(int i = 0 ; i < NUM_PIPES ; i++)
    {
        sf::Vector2f position;
        bool isFirstPipe = int(i / 2) == 0;
        sf::Vector2f dimensions = pipeSprites[i].getLocalBounds().getSize();
        position.x = screenWidth * (isFirstPipe ? 3 : 1) / 4 + int(isFirstPipe) * dimensions.x / 2;
        position.y = screenHeight * (i % 2 == 0 ? 6 : 0) / 6;
        
        pipeSprites[i].setPosition(position);
    }
}

bool Pipes::getIsError()
{
    return isError;
}