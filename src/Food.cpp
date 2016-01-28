//
//  Food.cpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#include "Food.hpp"

Food::Food(sf::Color color_, int size): color(color_) {
    shape.setRadius(size);

    int x = std::rand() % (Board::boardSize - 2 * Board::borderWidth - 2 * size) + Board::borderWidth;
    int y = std::rand() % (Board::boardSize - 2 * Board::borderWidth - 2 * size) + Board::borderWidth;
    shape.setPosition(x, y);
    shape.setFillColor(color);
}

void Food::changePosition() {
    int x = std::rand() % (Board::boardSize - 2 * Board::borderWidth - 2 * static_cast<int>(shape.getRadius())) + Board::borderWidth;
    int y = std::rand() % (Board::boardSize - 2 * Board::borderWidth - 2 * static_cast<int>(shape.getRadius())) + Board::borderWidth;
    shape.setPosition(x, y);
}

void Food::render(sf::RenderWindow& window) {
    window.draw(shape);
}

sf::CircleShape& Food::getShape() {
    return shape;
}