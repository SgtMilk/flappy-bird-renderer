#include "pipe.h"

#include <iostream>

const float Pipe::PIPE_SCALE = 0.4;
const float Pipe::SPEED = 500;

Pipe::Pipe(int InScreenWidth, int InScreenHeight, int InPipeNum)
{
    screenWidth = InScreenWidth;
    screenHeight = InScreenHeight;
    isTopPipe = InPipeNum % 2 == 1;
    isRightPipe = int(InPipeNum / 2) == 1;

    // pointer necessary otherwise the pointer changes
    pipeTexture = new sf::Texture();

    bool res = pipeTexture->loadFromFile("./lib/pipe.png");
    if(!res) {
        std::cout << "Cannot load pipe image. Exiting.\n";
        isError = true;
        return;
    };

    sprite.setTexture(*pipeTexture, true);
    sprite.setScale(PIPE_SCALE, PIPE_SCALE);

    if(isTopPipe) sprite.setRotation(180);

    sf::Vector2f dimensions = sprite.getLocalBounds().getSize();
    sprite.setOrigin(dimensions.x / 2, dimensions.y / 2);

    reset();

    isError = false;
}

void Pipe::updatePosition(float dt, float randHeight)
{
    float halfWidth = sprite.getLocalBounds().getSize().x / 2;
    sf::Vector2f pos = sprite.getPosition();
    pos.x -= SPEED * dt;

    if(pos.x < -1 * halfWidth) 
    {
        pos.x = screenWidth + halfWidth;
        pos.y = screenHeight * int(!isTopPipe) + randHeight;
        
    }
    sprite.setPosition(pos);
}

Bounds Pipe::getBounds()
{
    sf::FloatRect pipeRect = sprite.getGlobalBounds();
    Bounds bounds = {
        pipeRect.top,                       // top
        pipeRect.top + pipeRect.height,     // bottom
        pipeRect.left,                      // left
        pipeRect.left + pipeRect.width      // right
    };

    return bounds;
}

void Pipe::reset()
{
    sf::Vector2f position;
    float spriteWidth = sprite.getLocalBounds().getSize().x;

    // putting at 1/4 or 3/4 or the X axis to start plus an offset for the right pipe for the rotation logic
    position.x = screenWidth * (isRightPipe ? 0.75 : 0.25) + int(isRightPipe) * spriteWidth / 2;
    position.y = screenHeight * int(!isTopPipe);
    
    sprite.setPosition(position);
}

bool Pipe::getIsError()
{
    return isError;
}