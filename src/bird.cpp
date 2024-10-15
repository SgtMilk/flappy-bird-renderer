#include "bird.h"

#include <iostream>

const float Bird::BIRD_SCALE = 0.2;
const int Bird::COLLISION_TOLERANCE = 25;
const float Bird::JUMP_SPEED = -500;
const float Bird::ACCELERATION = 1000;
const float Bird::NEGATIVE_ACCELERATION = 2000;

Bird::Bird(sf::Vector2f InCenter)
{
    bool res = birdTexture.loadFromFile("./lib/bird.png");
    if(!res) {
        std::cout << "Cannot load bird image. Exiting.\n";
        isError = true;
        return;
    };

    sprite.setTexture(birdTexture, true);
    sprite.setScale(BIRD_SCALE, BIRD_SCALE);

    sf::Vector2f dimensions = sprite.getLocalBounds().getSize();
    sprite.setOrigin(dimensions.x / 2, dimensions.y / 2);
    reset(InCenter);

    isError = false;
}

void Bird::updatePosition(float dt)
{
    speed += (speed >= 0 ? NEGATIVE_ACCELERATION : ACCELERATION) * dt;

    sf::Vector2f position = sprite.getPosition();
    position.y += speed * dt;
    sprite.setPosition(position);
}

void Bird::jump()
{
    speed = JUMP_SPEED;
}

bool Bird::checkCollision(std::vector<Pipe> pipes){
    sf::Vector2f birdPos = sprite.getPosition();
    float width = sprite.getGlobalBounds().width;
    float height = sprite.getGlobalBounds().height;
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

        if(radius - distance > COLLISION_TOLERANCE) return true;
    }

    return false;
}

bool Bird::isOOO(int screenHeight){
    float y = sprite.getPosition().y;
    float limit = screenHeight / 4;

    return y < -1 * limit || y > limit + screenHeight;
}

void Bird::reset(sf::Vector2f center)
{
    sprite.setPosition(center);
    speed = 0;
}

bool Bird::getIsError()
{
    return isError;
}