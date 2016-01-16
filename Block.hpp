//
//  Block.hpp
//  Snake
//
//  Created by Vid Drobnic on 1/12/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#ifndef Block_hpp
#define Block_hpp

#include "Direction.hpp"
#include "Food.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

class Block {
    Direction direction;
    sf::RectangleShape shape;
    int thickness;
    bool changedDirection = false;
    
    void moveLastWithSpeed(int speed);
public:
    Block(int x, int y, int thickness_, Direction, sf::Color);
    void moveFirst(int speed);
    bool moveLast(bool food, Direction nextDirection, int speed); // Returns true if moving can continue (width and height > 0)
    sf::RectangleShape& getShape();
    Direction getDirection();
};

#endif /* Block_hpp */
