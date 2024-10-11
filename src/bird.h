#include <SFML/Graphics.hpp>

#ifndef BIRD_DEF
#define BIRD_DEF

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

    bool checkCollision(sf::Sprite *pipeSprites, int numPipes);
    bool isOOO(int screenHeight);

private:
    int frameRate;
 
    float speed;
    float acc;
    float negAcc;

    sf::Texture birdTexture;
    sf::Sprite bird;

    int collisionCounter;
};

#endif // BIRD_DEF