//
//  Snake.hpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#ifndef Snake_hpp
#define Snake_hpp

#include "Block.hpp"
#include "Direction.hpp"
#include "Food.hpp"

#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <vector>

class Game;

class Snake {
    std::vector<Block> blocks; // Last block is the head.
    int thickness;
    sf::Color color;
    Direction direction = Direction::Up;
    Food& food;
    int speed;
    
    bool foodCollision();
    bool selfCollision();
    bool borderCollision();
public:
    Snake(int thickness, int speed, sf::Color, Food&);
    bool move(Direction, Game&);
    bool move(Game&);
    void render(sf::RenderWindow&);
    void setSpeed(int);
};

#endif /* Snake_hpp */
