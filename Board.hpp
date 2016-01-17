//
//  Board.hpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#ifndef Board_hpp
#define Board_hpp

#include <SFML/Graphics.hpp>
#include <vector>

class Board {
    sf::RectangleShape top, bottom, left, right;
    sf::Color borderColor;
public:
    Board(sf::Color);
    void render(sf::RenderWindow&);
    
    static const int borderWidth = 15;
    static const int boardSize = 800;
};

#endif /* Board_hpp */
