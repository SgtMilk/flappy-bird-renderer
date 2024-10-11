#include <iostream>

#include "window.h"

int main(int, char**)
{
    std::cout << "Initializing\n";

    Window window(800, 600, 60);

    while(window.isOpen())
    {
        window.handleEvents();
        window.update();
    }
}
