//
//  main.cpp
//  Snake
//
//  Created by Vid Drobnic on 1/10/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#include "Game.hpp"
#include <iostream>

int main(int argc, const char * argv[]) {
    Game game(argv[0]);
    game.run();
    
    return 0;
}
