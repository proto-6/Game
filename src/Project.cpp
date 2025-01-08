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
// Movement and view are done, need to fix animation somehow working when pressing up or down arrow keys.
// 
// Game menu state:
// Develop game state (for now just a dummy) to test how transition works -
// 
// Main menu state:
// Make UI of main menu state +
// Make functionality of main menu -
// 
// Game menu state:
// Make game menu state -
// Develop game menu UI -
// Add functionality to game menu state -
// 
// Character state:
// Make character state (think about efficient mechanism to store) -
// Think about what character state needs ... -
// 
//
//
// DONE: :D
// Developed game engine
// Developer splash state
// Would be goo to implement flexibility of splash state depending of game resolution
// Created main menu state and implemented mechanism to move from state to state
// Add Lerp function somewhere so I've got no bugs
// Fixed hover on button breaking center point
// Fix hover button getting value of all buttons in MainMenu state
// 
//