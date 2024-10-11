#include <SFML/Graphics.hpp>

#ifndef PIPES_DEF
#define PIPES_DEF

#define NUM_PIPES 4
#define PIPE_SCALE 0.4
#define PIPE_OFFSET_RANGE 300

class Pipes
{
public:
    Pipes(int screenWidth, int screenHeight, int frameRate);
    ~Pipes();

    sf::Sprite *updatePosition();

private:
    sf::Texture pipeTexture;
    sf::Sprite *pipeSprites;

    int frameRate;
    float speed;

    int screenWidth;
    int screenHeight;
};

#endif // PIPES_DEF