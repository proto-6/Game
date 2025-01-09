#include <SFML/Graphics.hpp>
#include "Application.h"
#include <iostream>
#include <cassert>

#include "Button.h"
#include "Character.h"



int main()
{
    /*sf::RenderWindow a();
    auto modes = sf::VideoMode::getFullscreenModes();
    for (auto iter = modes.begin(); iter != modes.end(); ++iter)
    {
        std::cout << iter->width << "x" << iter->height << std::endl;
    }*/

    Application app(1920, 1080, "Magic Tinkerer");


    app.Run();


    
    return 0;
}

// TODO: :)
// Urgency:
// Resize map when character is moving so he doesn't walk in emptiness
// Can be done using position of character e.g. if character moved 64px (yes, tile is 16x16 but I scaled it by 4) 
// to the right then call method in map class that resize map in that direction.
// You can make 4 methods for all directions
//
// 
// 
//