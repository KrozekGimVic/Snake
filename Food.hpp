//
//  Food.hpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#ifndef Food_hpp
#define Food_hpp

#include "Board.hpp"
#include <stdlib.h>
#include <SFML/Graphics.hpp>

class Food {
    sf::CircleShape shape;
    sf::Color color;
public:
    Food(sf::Color, int size);
    void changePosition();
    void render(sf::RenderWindow&);
    sf::CircleShape& getShape();
};

#endif /* Food_hpp */
