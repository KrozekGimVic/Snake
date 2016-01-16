//
//  Game.hpp
//  Snake
//
//  Created by Vid Drobnic on 1/13/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include "Board.hpp"
#include "Food.hpp"
#include "Snake.hpp"

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

class Game {
    sf::RenderWindow window;
    Board board;
    Food food;
    Snake snake;
    
    void update();
    void render();
public:
    Game();
    void run();
};

#endif /* Game_hpp */
