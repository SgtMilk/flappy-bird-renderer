#pragma once

#include <SFML/Graphics.hpp>

struct Bounds{
    float top;
    float bottom;
    float left;
    float right;
};

class Pipe
{
public:

    // constants
    static const float PIPE_SCALE;
    static const float SPEED_PER_SECOND;

    Pipe(int screenWidth, int screenHeight, int frameRate, int pipeNum);

    sf::Sprite updatePosition(float randHeight);

    Bounds getBounds();

    void reset();

    bool getIsError();

private:
    sf::Texture *pipeTexture;
    sf::Sprite pipeSprite;
    
    bool isTopPipe;
    bool isRightPipe;

    int frameRate;
    float speed;

    int screenWidth;
    int screenHeight;

    bool isError;
};