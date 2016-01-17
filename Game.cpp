//
//  Game.cpp
//  Snake
//
//  Created by Vid Drobnic on 1/13/16.
//  Copyright © 2016 Vid Drobnic. All rights reserved.
//

#include "Game.hpp"
#include "Snake.hpp"

Game::Game(std::string runPath): board(sf::Color::Red), food(sf::Color::Blue, 15) {
    snake = new Snake(20, 2, sf::Color::Green, food);
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    window.create(sf::VideoMode(Board::boardSize, Board::boardSize), "Snake", sf::Style::Titlebar | sf::Style::Close, settings);
    window.setVerticalSyncEnabled(true);
    window.setFramerateLimit(60);

    font.loadFromFile("Font.ttf");
    scoreText = sf::Text("Score: " + std::to_string(score), font, 40);
    scoreText.setColor(sf::Color::White);
    positionScore();
}

Game::~Game() {
    delete snake;
}

void Game::run() {
    double timeDelta = 0;
    const double time = 1000.0 / 60.0;
    auto previusTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    
    while (window.isOpen()) {
        auto now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
        timeDelta += now.count() - previusTime.count();
        previusTime = now;
        
        while (timeDelta > time) {
            update();
            
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
            }
            
            timeDelta -= time;
        }
        
        render();
    }
}

void Game::update() {
    bool snakeMoved;
    
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
            snakeMoved = snake->move(Direction::Up, *this);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
            snakeMoved = snake->move(Direction::Down, *this);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
            snakeMoved = snake->move(Direction::Left, *this);
        } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
            snakeMoved = snake->move(Direction::Right, *this);
        }
    } else {
        snakeMoved = snake->move(*this);
    }
    
    if (!snakeMoved) {
        std::cout << "You lose." << std::endl;
        //exit(0);
        snake->setSpeed(0);
    } else {
        snake->setSpeed(score / 5 + 2);
    }
}

void Game::render() {
    window.clear();
    board.render(window);
    food.render(window);
    snake->render(window);
    window.draw(scoreText);
    window.display();
}

void Game::positionScore() {
    int x = Board::boardSize - Board::borderWidth - scoreText.getLocalBounds().width - 15;
    int y = Board::borderWidth;
    scoreText.setPosition(x, y);
}

int Game::getScore() {
    return score;
}

void Game::setScore(int newScore) {
    score = newScore;
    scoreText.setString("Score: " + std::to_string(score));
    positionScore();
}

void Game::addOneToScore() {
    setScore(++score);
}