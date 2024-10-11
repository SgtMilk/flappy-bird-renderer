#include <SFML/Graphics.hpp>

#define BIRD_SCALE 0.2
#define COLLISION_TOLERANCE 25
#define COLLISION_TO_TRIGGER 300

#ifndef BIRD_DEF
#define BIRD_DEF

class Bird
{
public:
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
    float collisionsToTrigger;
};

#endif // BIRD_DEF