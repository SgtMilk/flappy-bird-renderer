#include <iostream>

#include "window.h"

// constants
static const int screenWidth = 800;
static const int screenHeight = 600;
static const int frameRate = 60;

int main(int, char**)
{
    Window window(screenWidth, screenHeight, frameRate);

    while(window.isOpen())
    {
        window.handleEvents();
        window.update();
    }
}
