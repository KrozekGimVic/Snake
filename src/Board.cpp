//
//  Board.cpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#include "Board.hpp"

Board::Board(sf::Color color_): borderColor(color_) {
    top.setPosition(0, 0);
    top.setSize(sf::Vector2f(boardSize, borderWidth));
    
    bottom.setPosition(0, boardSize - borderWidth);
    bottom.setSize(sf::Vector2f(boardSize, borderWidth));
    
    left.setPosition(0, borderWidth);
    left.setSize(sf::Vector2f(borderWidth, boardSize - 2 * borderWidth));
    
    right.setPosition(boardSize - borderWidth, borderWidth);
    right.setSize(sf::Vector2f(borderWidth, boardSize - 2 * borderWidth));
    
    top.setFillColor(borderColor);
    bottom.setFillColor(borderColor);
    left.setFillColor(borderColor);
    right.setFillColor(borderColor);
}

void Board::render(sf::RenderWindow& window) {
    window.draw(top);
    window.draw(bottom);
    window.draw(left);
    window.draw(right);
}