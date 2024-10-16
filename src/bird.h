#pragma once

#include "pipe.h"

#include <SFML/Graphics.hpp>

class Bird
{
public:

    // constants
    static const float BIRD_SCALE;
    static const int COLLISION_TOLERANCE;
    static const float JUMP_SPEED;
    static const float ACCELERATION;
    static const float NEGATIVE_ACCELERATION;
    
    Bird(sf::Vector2f center);

    void updatePosition(float dt);
    void jump();

    bool checkCollision(std::vector<Pipe> pipes);
    bool isOOO(int screenHeight);

    void reset(sf::Vector2f center);

    bool getIsError();

    sf::Sprite sprite;

private:
    float speed;

    sf::Texture birdTexture;

    bool isError;
};