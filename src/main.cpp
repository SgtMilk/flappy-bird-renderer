#include <iostream>

#include "window.h"

// constants
static const int screenWidth = 800;
static const int screenHeight = 600;

int main(int, char**)
{
    Window window(screenWidth, screenHeight);
    window.run();
}
