#include "bird.h"

#include <iostream>

const float Bird::BIRD_SCALE = 0.2;
const int Bird::COLLISION_TOLERANCE = 25;
const int Bird::NUM_COLLISIONS_TO_TRIGGER_PER_SECOND = 300;

Bird::Bird(sf::Vector2f InCenter, int InFrameRate)
{
    frameRate = InFrameRate;

    bool res = birdTexture.loadFromFile("./lib/bird.png");
    if(!res) {
        std::cout << "Cannot load bird image. Exiting.\n";
        isError = true;
        return;
    };

    bird.setTexture(birdTexture, true);
    bird.setScale(BIRD_SCALE, BIRD_SCALE);

    sf::Vector2f dimensions = bird.getLocalBounds().getSize();
    bird.setOrigin(dimensions.x / 2, dimensions.y / 2);
    reset(InCenter);

    acc = 9.8 / frameRate * 1.5;
    negAcc = acc * 2;

    collisionCounter = 0;
    NUM_COLLISIONS_TO_TRIGGER = NUM_COLLISIONS_TO_TRIGGER_PER_SECOND / frameRate;

    isError = false;
}

sf::Sprite Bird::updatePosition()
{
    speed += (speed >= 0 ? negAcc : acc);

    sf::Vector2f position = bird.getPosition();
    position.y += speed;
    bird.setPosition(position);

    return bird;
}

void Bird::jump()
{
    speed = -7;
}

bool Bird::checkCollision(std::vector<Pipe> pipes){
    sf::Vector2f birdPos = bird.getPosition();
    float width = bird.getGlobalBounds().width;
    float height = bird.getGlobalBounds().height;
    float radius = (width < height ? width : height);

    bool isCollision = false;
    
    for(int i = 0 ; i < pipes.size() ; i++)
    {
        // circle to rectangle collision detection
        Bounds pipeRect = pipes[i].getBounds();
        float testX = birdPos.x;
        float testY = birdPos.y;

        // finding right or left to test (otherwise distX = 0)
        if(birdPos.x < pipeRect.left) testX  = pipeRect.left;
        else if(birdPos.x > pipeRect.right) testX = pipeRect.right;

        // finding top or bottom to test (otherwise distY = 0)
        if(birdPos.y < pipeRect.top) testY  = pipeRect.top;
        else if(birdPos.y > pipeRect.bottom) testY = pipeRect.bottom;

        float distX = birdPos.x - testX;
        float distY = birdPos.y - testY;
        float distance = sqrt(pow(distX, 2) + pow(distY, 2)); 

        if(radius - distance > COLLISION_TOLERANCE)
        {
            collisionCounter++;
            isCollision = true;
            if(collisionCounter > NUM_COLLISIONS_TO_TRIGGER) return true;
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

void Bird::reset(sf::Vector2f center)
{
    bird.setPosition(center);
    speed = 0;
}

bool Bird::getIsError()
{
    return isError;
}