#include "pipe.h"

#include <iostream>

const float Pipe::PIPE_SCALE = 0.4;
const float Pipe::SPEED_PER_SECOND = 500;

Pipe::Pipe(int InScreenWidth, int InScreenHeight, int InFrameRate, int InPipeNum)
{
    frameRate = InFrameRate;
    speed = SPEED_PER_SECOND / frameRate;
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

    pipeSprite.setTexture(*pipeTexture, true);
    pipeSprite.setScale(PIPE_SCALE, PIPE_SCALE);

    if(!isTopPipe) pipeSprite.setRotation(180);

    sf::Vector2f dimensions = pipeSprite.getLocalBounds().getSize();
    pipeSprite.setOrigin(dimensions.x / 2, dimensions.y / 2);

    reset();

    isError = false;
}

sf::Sprite Pipe::updatePosition(float randHeight)
{
    float halfWidth = pipeSprite.getLocalBounds().getSize().x / 2;
    sf::Vector2f pos = pipeSprite.getPosition();
    pos.x -= speed;

    if(pos.x < -1 * halfWidth) 
    {
        pos.x = screenWidth + halfWidth;
        pos.y = screenHeight * int(isTopPipe) + randHeight;
        
    }
    pipeSprite.setPosition(pos);

    return pipeSprite;
}

Bounds Pipe::getBounds()
{
    sf::FloatRect pipeRect = pipeSprite.getGlobalBounds();
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
    float spriteWidth = pipeSprite.getLocalBounds().getSize().x;

    // putting at 1/4 or 3/4 or the X axis to start plus an offset for the right pipe for the rotation logic
    position.x = screenWidth * (isRightPipe ? 0.75 : 0.25) + int(isRightPipe) * spriteWidth / 2;
    position.y = screenHeight * int(isTopPipe);
    
    pipeSprite.setPosition(position);
}

bool Pipe::getIsError()
{
    return isError;
}