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
    static const float SPEED;

    Pipe(int screenWidth, int screenHeight, int pipeNum);

    void updatePosition(float dt, float randHeight);

    Bounds getBounds();

    void reset();

    bool getIsError();

    sf::Sprite sprite;

private:
    sf::Texture *pipeTexture;
    
    bool isTopPipe;
    bool isRightPipe;

    int screenWidth;
    int screenHeight;

    bool isError;
};