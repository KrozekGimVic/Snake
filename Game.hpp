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

#include <SFML/Graphics.hpp>
#include <chrono>
#include <iostream>

class Snake;

class Game {
    sf::RenderWindow window;
    Board board;
    Food food;
    Snake* snake;
    int score = 0;
    sf::Text scoreText;
    sf::Font font;
    
    void update();
    void render();
    void positionScore();
public:
    Game(std::string runPath);
    ~Game();
    void run();
    void setScore(int);
    void addOneToScore();
    int getScore();
};

#endif /* Game_hpp */
