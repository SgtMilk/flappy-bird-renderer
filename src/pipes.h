#pragma once

#include <SFML/Graphics.hpp>

class Pipes
{
public:

    // constants
    static const int NUM_PIPES;
    static const float PIPE_SCALE;
    static const int PIPE_OFFSET_RANGE;
    static const float SPEED_PER_SECOND;

    Pipes(int screenWidth, int screenHeight, int frameRate);

    std::vector<sf::Sprite> updatePosition();

    void reset();

    bool getIsError();

private:
    sf::Texture pipeTexture;
    std::vector<sf::Sprite> pipeSprites;

    int frameRate;
    float speed;

    int screenWidth;
    int screenHeight;

    bool isError;
};