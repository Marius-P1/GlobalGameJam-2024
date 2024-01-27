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
    this->_player1->handleEvent(event);
    this->_player2->handleEvent(event);
}

void Game::update()
{
    this->_player1->update();
    this->_player2->update();

    if (isColliding(this->_player1)) {
        this->_player1->stateFly(false);
        this->_player1->resetJump();
        this->_player1->setPlayerPos(this->_player1->getOldPlayerPos());
    }
    if (isColliding(this->_player2)) {
        this->_player2->stateFly(false);
        this->_player2->resetJump();
        this->_player2->setPlayerPos(this->_player2->getOldPlayerPos());
    }
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

bool Game::isColliding(Player *player)
{
    std::vector<sf::RectangleShape> colision = this->_map->getColision();

    for (size_t i = 0; i < this->_map->getNbCollisionShape(); i++) {
        if (player->isColliding(colision[i]))
            return true;
    }
    return false;
}
