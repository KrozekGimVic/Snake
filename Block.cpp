//
//  Block.cpp
//  Snake
//
//  Created by Vid Drobnic on 1/12/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#include "Block.hpp"

sf::RectangleShape& Block::getShape() {
    return shape;
}

Direction Block::getDirection() {
    return direction;
}

bool Block::moveLast(bool food, Direction nextDirection, int speed) {
    float width = shape.getSize().x;
    float height = shape.getSize().y;
    float x = shape.getPosition().x;
    float y = shape.getPosition().y;
    
    int difference = -1;
    
    switch (direction) {
        case Direction::Up:
            height -= speed;
            if (food) {
                height += thickness;
            }
            
            if (height < thickness && !changedDirection) {
                difference = thickness - height;
                height = thickness;
                direction = nextDirection;
                changedDirection = true;
                moveLastWithSpeed(difference);
            }
            break;
        case Direction::Down:
            height -= speed;
            y += speed;
            if (food) {
                height += thickness;
                y -= thickness;
            }
            
            if (height < thickness && !changedDirection) {
                difference = thickness - height;
                y -= difference;
                height = thickness;
                direction = nextDirection;
                changedDirection = true;
                moveLastWithSpeed(difference);
            }
            break;
        case Direction::Left:
            width -= speed;
            if (food) {
                width += thickness;
            }
            
            if (width < thickness && !changedDirection) {
                difference = thickness - width;
                width = thickness;
                direction = nextDirection;
                changedDirection = true;
                moveLastWithSpeed(difference);
            }
            break;
        case Direction::Right:
            width -= speed;
            x += speed;
            if (food) {
                width += thickness;
                x -= thickness;
            }
            
            if (width < thickness && !changedDirection) {
                difference = thickness - width;
                x -= difference;
                width = thickness;
                direction = nextDirection;
                changedDirection = true;
                moveLastWithSpeed(difference);
            }
            break;
    }
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
    
    if (difference > -1)
        moveLastWithSpeed(difference);
    
    return width > 0 && height > 0;
}

void Block::moveLastWithSpeed(int speed) {
    float width = shape.getSize().x;
    float height = shape.getSize().y;
    float x = shape.getPosition().x;
    float y = shape.getPosition().y;
    
    switch (direction) {
        case Direction::Up:
            height -= speed;
            break;
        case Direction::Down:
            height -= speed;
            y += speed;
            break;
        case Direction::Left:
            width -= speed;
            break;
        case Direction::Right:
            width -= speed;
            x += speed;
            break;
    }
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
}

void Block::moveFirst(int speed) {
    float width = shape.getSize().x;
    float height = shape.getSize().y;
    float x = shape.getPosition().x;
    float y = shape.getPosition().y;
    
    switch (direction) {
        case Direction::Up:
            height += speed;
            y -= speed;
            break;
        case Direction::Down:
            height += speed;
            break;
        case Direction::Left:
            width += speed;
            x -= speed;
            break;
        case Direction::Right:
            width += speed;
            break;
    }
    
    shape.setSize(sf::Vector2f(width, height));
    shape.setPosition(x, y);
}

Block::Block(int x, int y, int thickness_, Direction direction_, sf::Color color): direction(direction_), thickness(thickness_) {
    shape.setPosition(x, y);
    shape.setFillColor(color);
    
    if (direction == Direction::Up || direction == Direction::Down)
        shape.setSize(sf::Vector2f(thickness, 0));
    else
        shape.setSize(sf::Vector2f(0, thickness));
}