//
//  Snake.cpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#include "Snake.hpp"
#include "Game.hpp"

int square(int value) {
    return value * value;
}

bool intersects(int min_x_1, int max_x_1, int min_y_1, int max_y_1, int min_x_2, int max_x_2, int min_y_2, int max_y_2) {
    if (((min_x_2 >= min_x_1 && min_x_2 <= max_x_1) || (max_x_2 >= min_x_1 && max_x_2 <= max_x_1)) &&
        ((min_y_2 >= min_y_1 && min_y_2 <= max_y_1) || (max_y_2 >= min_y_1 && max_y_2 <= max_y_1))) {
        return true;
    }
    
    return false;
}

bool intersectsSelf(int min_x_1, int max_x_1, int min_y_1, int max_y_1, int min_x_2, int max_x_2, int min_y_2, int max_y_2) {
    if (((min_x_2 > min_x_1 && min_x_2 < max_x_1) || (max_x_2 > min_x_1 && max_x_2 < max_x_1)) &&
        ((min_y_2 > min_y_1 && min_y_2 < max_y_1) || (max_y_2 > min_y_1 && max_y_2 < max_y_1))) {
        return true;
    }
    
    return false;
}

Snake::Snake(int thickness_, int speed_, sf::Color color_, Food& food_): thickness(thickness_), color(color_), food(food_), speed(speed_) {
    const int x = Board::boardSize / 2 - thickness / 2;
    const int y = Board::boardSize / 2 - thickness / 2;
    Block firstBlock(x, y, thickness, direction, color);
    firstBlock.getShape().setSize(sf::Vector2f(thickness, 3 * thickness));
    
    blocks.push_back(firstBlock);
}

bool Snake::move(Direction newDirection, Game& game) {
    if (newDirection == direction) {
        return move(game);
    }
    
    const sf::RectangleShape firstShape = blocks[blocks.size() - 1].getShape();
    int x;
    int y;
    
    if (direction == Direction::Up && newDirection == Direction::Left) {
        x = firstShape.getPosition().x;
        y = firstShape.getPosition().y;
    } else if (direction == Direction::Up && newDirection == Direction::Right) {
        x = firstShape.getPosition().x + thickness;
        y = firstShape.getPosition().y;
    } else if (direction == Direction::Left && newDirection == Direction::Up) {
        x = firstShape.getPosition().x;
        y = firstShape.getPosition().y;
    } else if (direction == Direction::Left && newDirection == Direction::Down) {
        x = firstShape.getPosition().x;
        y = firstShape.getPosition().y + thickness;
    } else if (direction == Direction::Down && newDirection == Direction::Left) {
        x = firstShape.getPosition().x;
        y = firstShape.getPosition().y + firstShape.getSize().y - thickness;
    } else if (direction == Direction::Down && newDirection == Direction::Right) {
        x = firstShape.getPosition().x + thickness;
        y = firstShape.getPosition().y + firstShape.getSize().y - thickness;
    } else if (direction == Direction::Right && newDirection == Direction::Up) {
        x = firstShape.getPosition().x + firstShape.getSize().x - thickness;
        y = firstShape.getPosition().y;
    } else if (direction == Direction::Right && newDirection == Direction::Down) {
        x = firstShape.getPosition().x + firstShape.getSize().x - thickness;
        y = firstShape.getPosition().y + thickness;
    } else {
        return move(game);
    }
    
    Block block = Block(x, y, thickness, newDirection, color);
    blocks.push_back(block);
    
    direction = newDirection;
    return move(game);
}

bool Snake::move(Game& game) {
    blocks[blocks.size() - 1].moveFirst(speed);
    Direction nextDirection;
    if (blocks.size() < 2) {
        nextDirection = blocks[0].getDirection();
    } else {
        nextDirection = blocks[1].getDirection();
    }
    
    bool colidedWithFood = foodCollision();
    
    if (!blocks[0].moveLast(colidedWithFood, nextDirection, speed)) {
        blocks.erase(blocks.begin());
    }
    
    if (colidedWithFood) game.addOneToScore();
    
    return !(selfCollision() || borderCollision());
}

bool Snake::foodCollision() {
    sf::RectangleShape headShape = blocks[blocks.size() - 1].getShape();
    
    int center_x = food.getShape().getPosition().x + food.getShape().getRadius();
    int center_y = food.getShape().getPosition().y + food.getShape().getRadius();
    int radius = food.getShape().getRadius();
    int squaredRadius = radius * radius;
    
    if (direction == Direction::Up) {
        int x_1 = headShape.getPosition().x;
        int x_2 = x_1 + headShape.getSize().x;
        int y = headShape.getPosition().y;
        
        int yDifferenceSquared = square(y - center_y);
        
        if (yDifferenceSquared + square(x_1 - center_x) <= squaredRadius || yDifferenceSquared + square(x_2 - center_x) <= squaredRadius) {
            food.changePosition();
            return true;
        }
    } else if (direction == Direction::Down) {
        int x_1 = headShape.getPosition().x;
        int x_2 = x_1 + headShape.getSize().x;
        int y = headShape.getPosition().y + headShape.getSize().y;
        
        int yDifferenceSquared = square(y - center_y);
        
        if (yDifferenceSquared + square(x_1 - center_x) <= squaredRadius || yDifferenceSquared + square(x_2 - center_x) <= squaredRadius) {
            food.changePosition();
            return true;
        }
    } else if (direction == Direction::Left) {
        int x = headShape.getPosition().x;
        int y_1 = headShape.getPosition().y;
        int y_2 = y_1 + headShape.getSize().y;
        
        int xDifferenceSquared = square(x - center_x);
        
        if (xDifferenceSquared + square(y_1 - center_y) <= squaredRadius || xDifferenceSquared + square(y_2 - center_y) <= squaredRadius) {
            food.changePosition();
            return true;
        }
    } else {
        int x = headShape.getPosition().x + headShape.getSize().x;
        int y_1 = headShape.getPosition().y;
        int y_2 = y_1 + headShape.getSize().y;
        
        int xDifferenceSquared = square(x - center_x);
        
        if (xDifferenceSquared + square(y_1 - center_y) <= squaredRadius || xDifferenceSquared + square(y_2 - center_y) <= squaredRadius) {
            food.changePosition();
            return true;
        }
    }
    
    return false;
}

bool Snake::selfCollision() {
    for (int i = 0; i < blocks.size(); ++i) {
        sf::RectangleShape shape1 = blocks[i].getShape();
        int min_x_1 = shape1.getPosition().x;
        int max_x_1 = min_x_1 + shape1.getSize().x;
        int min_y_1 = shape1.getPosition().y;
        int max_y_1 = min_y_1 + shape1.getSize().y;
        
        for (int j = i + 1; j < blocks.size(); ++j) {
            sf::RectangleShape shape2 = blocks[j].getShape();
            int min_x_2 = shape2.getPosition().x;
            int max_x_2 = min_x_2 + shape2.getSize().x;
            int min_y_2 = shape2.getPosition().y;
            int max_y_2 = min_y_2 + shape2.getSize().y;
            
            if (intersectsSelf(min_x_1, max_x_1, min_y_1, max_y_1, min_x_2, max_x_2, min_y_2, max_y_2)) {
                return true;
            }
        }
    }
    
    return false;
}

bool Snake::borderCollision() {
    for (Block block : blocks) {
        sf::RectangleShape shape = block.getShape();
        int x_min_2 = shape.getPosition().x;
        int x_max_2 = x_min_2 + shape.getSize().x;
        int y_min_2 = shape.getPosition().y;
        int y_max_2 = y_min_2 + shape.getSize().y;
        
        int top_min_x = 0;
        int top_max_x = Board::boardSize;
        int top_min_y = 0;
        int top_max_y = Board::borderWidth;
        
        int bottom_min_x = top_min_x;
        int bottom_max_x = top_max_x;
        int bottom_min_y = Board::boardSize - Board::borderWidth;
        int bottom_max_y = Board::boardSize;
        
        int left_min_x = 0;
        int left_max_x = Board::borderWidth;
        int left_min_y = Board::borderWidth;
        int left_max_y = Board::boardSize - 2 * Board::borderWidth;
        
        int rigth_min_x = Board::boardSize - Board::borderWidth;
        int rigth_max_x = Board::boardSize;
        int right_min_y = left_min_y;
        int right_max_y = left_max_y;
        
        if (intersects(top_min_x, top_max_x, top_min_y, top_max_y, x_min_2, x_max_2, y_min_2, y_max_2) ||
            intersects(bottom_min_x, bottom_max_x, bottom_min_y, bottom_max_y, x_min_2, x_max_2, y_min_2, y_max_2) ||
            intersects(left_min_x, left_max_x, left_min_y, left_max_y, x_min_2, x_max_2, y_min_2, y_max_2) ||
            intersects(rigth_min_x, rigth_max_x, right_min_y, right_max_y, x_min_2, x_max_2, y_min_2, y_max_2)) {
            return true;
        }
    }
    
    return false;
}

void Snake::setSpeed(int newSpeed) {
    speed = newSpeed;
}

void Snake::render(sf::RenderWindow& window) {
    for (auto& block : blocks) {
        window.draw(block.getShape());
    }
}