/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Game
*/

#include "./game/Game.hpp"

Game::Game()
{
    init();
}

Game::~Game()
{
}

void Game::handleEvent(sf::Event event)
{
    this->_player1->handleEvent(event, this->_map);
    this->_player2->handleEvent(event, this->_map);
}

void Game::update()
{
    this->_player1->update(this->_map);
    this->_player2->update(this->_map);
}

void Game::draw(sf::RenderWindow &window)
{
    this->_map->draw(window);

    this->_player1->draw(window);
    this->_player2->draw(window);
}

void Game::init()
{
    this->_map = new Map();
    this->_player1 = new Player(PlayerType::PLAYER1);
    this->_player2 = new Player(PlayerType::PLAYER2);
}
