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
    this->_player->handleEvent(event);
}

void Game::update()
{
    this->_player->update();
    if (isColliding())
        this->_player->setPlayerPos(this->_player->getOldPlayerPos());
}

void Game::draw(sf::RenderWindow &window)
{
    this->_player->draw(window);
    this->_map->draw(window);
}

void Game::init()
{
    this->_map = new Map();
    this->_player = new Player();
}

bool Game::isColliding()
{
    std::vector<sf::Vector2f> points = this->_player->getColisionPoints();

    for (size_t i = 0; i < points.size(); i++) {
        if (points[i].x < 0 || points[i].y < 0 || points[i].x > this->_map->getColisionImage().getSize().x || points[i].y > this->_map->getColisionImage().getSize().y)
            return true;
        sf::Color pixel = this->_map->getColisionImage().getPixel(points[i].x, points[i].y);
        if (pixel == sf::Color::Red) {
            std::cout << "COLLISION in " << points[i].x << " " << points[i].y << std::endl;
            return true;
        }
    }
    return false;
}
