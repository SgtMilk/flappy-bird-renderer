#include "bird.h"
#include "SFML/Window.hpp"

#include <iostream>

Bird::Bird(sf::Vector2f center, int frameRate)
{
    bool res = birdTexture.loadFromFile("./lib/bird.png");
    if(!res) std::cout << "Cannot load bird\n";
    bird.setTexture(birdTexture, true);
    bird.setScale(BIRD_SCALE, BIRD_SCALE);

    sf::Vector2f dimensions = bird.getLocalBounds().getSize();
    this->bird.setOrigin(dimensions.x / 2, dimensions.y / 2);
    this->bird.setPosition(center);

    speed = 0;
    this->frameRate = frameRate;

    acc = 9.8 / frameRate * 1.5;
    negAcc = acc * 2;

    collisionCounter = 0;
    collisionsToTrigger = COLLISION_TO_TRIGGER / frameRate;
}

sf::Sprite Bird::updatePosition()
{
    speed += (speed >= 0 ? negAcc : acc);

    sf::Vector2f position = this->bird.getPosition();
    position.y += speed;
    bird.setPosition(position);

    return bird;
}

void Bird::jump()
{
    speed = -7;
}

bool Bird::checkCollision(sf::Sprite *pipeSprites, int numPipes){
    sf::Vector2f birdPos = bird.getPosition();
    float width = bird.getGlobalBounds().width;
    float height = bird.getGlobalBounds().height;
    float radius = (width < height ? width : height);

    bool isCollision = false;
    
    for(int i = 0 ; i < numPipes ; i++)
    {
        sf::FloatRect pipeRect = pipeSprites[i].getGlobalBounds();
        float testX = birdPos.x;
        float testY = birdPos.y;

        if(birdPos.x < pipeRect.left) testX  = pipeRect.left;
        else if(birdPos.x > pipeRect.left + pipeRect.width) testX = pipeRect.left + pipeRect.width;

        if(birdPos.y < pipeRect.top) testY  = pipeRect.top;
        else if(birdPos.y > pipeRect.top + pipeRect.height) testY = pipeRect.top + pipeRect.height;

        float distX = birdPos.x - testX;
        float distY = birdPos.y - testY;
        float distance = sqrt((distX * distX) + (distY * distY)); 

        if(radius - distance > COLLISION_TOLERANCE)
        {
            collisionCounter++;
            isCollision = true;
            if(collisionCounter > collisionsToTrigger) return true;
        }
    }

    if(!isCollision) collisionCounter = 0;
    return false;
}

bool Bird::isOOO(int screenHeight){
    float y = bird.getPosition().y;
    float limit = screenHeight / 4;

    return y < -1 * limit || y > limit + screenHeight;
}