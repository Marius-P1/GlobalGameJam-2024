/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Map
*/

#include "./map/Map.hpp"

Map::Map()
{
    init();
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(this->_mapSprite);
}

sf::Image Map::getColisionImage()
{
    return this->_colisionImage;
}

void Map::init()
{
    initTexture();
    initSprite();
    initColision();
    initPos();
}

void Map::initSprite()
{
    this->_mapSprite.setTexture(this->_mapTexture);
}

void Map::initTexture()
{
    this->_mapTexture.loadFromFile("assets/map/mapTest.png");
}

void Map::initColision()
{
    this->_colisionImage.loadFromFile("assets/map/mapTest_colision.png");
    this->_colisionTexture.loadFromImage(this->_colisionImage);
}

void Map::initPos()
{
    this->_mapSprite.setPosition(0, 0);
}
