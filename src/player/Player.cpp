/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Player
*/

#include "./player/Player.hpp"

Player::Player()
{
    init();
}

Player::~Player()
{
}

void Player::handleEvent(sf::Event event)
{
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Z) {
            move(sf::Vector2f(0, -10));
        }
        if (event.key.code == sf::Keyboard::S) {
            move(sf::Vector2f(0, 10));
        }
        if (event.key.code == sf::Keyboard::Q) {
            move(sf::Vector2f(-10, 0));
        }
        if (event.key.code == sf::Keyboard::D) {
            move(sf::Vector2f(10, 0));
        }
    }
}

void Player::update()
{
}

void Player::draw(sf::RenderWindow &window)
{
    window.draw(this->_player);
}

void Player::move(sf::Vector2f move)
{
    this->_oldPlayerPos = this->_playerPos;
    this->_playerPos += move;
    this->_player.setPosition(this->_playerPos);
}

std::vector<sf::Vector2f> Player::getColisionPoints()
{
    std::vector<sf::Vector2f> points = std::vector<sf::Vector2f>();

    points.push_back(sf::Vector2f(this->_playerPos.x, this->_playerPos.y));
    points.push_back(sf::Vector2f(this->_playerPos.x + this->_player.getGlobalBounds().width, this->_playerPos.y));
    points.push_back(sf::Vector2f(this->_playerPos.x, this->_playerPos.y + this->_player.getGlobalBounds().height));
    points.push_back(sf::Vector2f(this->_playerPos.x + this->_player.getGlobalBounds().width, this->_playerPos.y + this->_player.getGlobalBounds().height));
    return points;
}

sf::Vector2f Player::getOldPlayerPos() const
{
    return this->_oldPlayerPos;
}

void Player::setPlayerPos(sf::Vector2f pos)
{
    this->_playerPos = pos;
    this->_player.setPosition(this->_playerPos);
}

void Player::init()
{
    initTexture();
    initSprite();
    initPos();
    // initOrigin();
    this->_player.setScale(0.5, 0.5);
    initSpeed();
    this->_oldPlayerPos = this->_playerPos;
}

void Player::initSprite()
{
    this->_player.setTexture(this->_playerTexture);
}

void Player::initTexture()
{
    this->_playerTexture.loadFromFile("assets/player/player.png");
}

void Player::initPos()
{
    this->_playerPos = sf::Vector2f(0, 0);
    this->_player.setPosition(this->_playerPos);
}

void Player::initOrigin()
{
    this->_playerOrigin = sf::Vector2f(0, 0);
    this->_player.setOrigin(this->_playerOrigin);
}

void Player::initSpeed()
{
    this->_playerSpeed = sf::Vector2f(0, 0);
}

void Player::clean()
{
}

