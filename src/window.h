#include <SFML/Graphics.hpp>

#include "bird.h"
#include "pipes.h"

#ifndef WINDOW_DEF
#define WINDOW_DEF

class Window
{
public:
    Window(int screenWidth, int screenHeight, int frameRate);

    void handleEvents();
    bool isOpen();

    void update();
    void reset();
private:
    sf::RenderWindow window;

    float frameRate;
    sf::Time frameTime;
    sf::Clock clk;

    Bird *bird;
    Pipes *pipes;

    float positionX;
};

#endif // WINDOW_DEF