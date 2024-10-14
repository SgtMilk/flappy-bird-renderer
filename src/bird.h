#pragma once

#include "pipe.h"

#include <SFML/Graphics.hpp>

class Bird
{
public:

    // constants
    static const float BIRD_SCALE;
    static const int COLLISION_TOLERANCE;
    static const int NUM_COLLISIONS_TO_TRIGGER_PER_SECOND;
    int NUM_COLLISIONS_TO_TRIGGER;
    
    Bird(sf::Vector2f center, int frameRate);

    sf::Sprite updatePosition();
    void jump();

    bool checkCollision(std::vector<Pipe> pipes);
    bool isOOO(int screenHeight);

    void reset(sf::Vector2f center);

    bool getIsError();

private:
    int frameRate;
 
    float speed;
    float acc;
    float negAcc;

    sf::Texture birdTexture;
    sf::Sprite bird;

    int collisionCounter;

    bool isError;
};