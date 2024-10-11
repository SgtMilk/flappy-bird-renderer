#include <SFML/Graphics.hpp>

#ifndef PIPES_DEF
#define PIPES_DEF

class Pipes
{
public:

    // constants
    static const int NUM_PIPES;
    static const float PIPE_SCALE;
    static const int PIPE_OFFSET_RANGE;
    static const float SPEED_PER_SECOND;

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