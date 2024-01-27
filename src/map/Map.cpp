/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Map
*/

#include "./map/Map.hpp"

Map::Map(MapType type)
{
    init(type);
}

Map::~Map()
{
}

void Map::draw(sf::RenderWindow &window)
{
    window.draw(this->_mapSprite);
    // for (size_t i = 0; i < this->_colision.size(); i++) {
    //     window.draw(this->_colision[i]);
    // }
}

std::vector<sf::RectangleShape> Map::getColision()
{
    return this->_colision;
}

size_t Map::getNbCollisionShape()
{
    return this->_nbCollisionShape;
}

void Map::init(MapType type)
{
    initTexture();
    initSprite();
    initColision(type);
    initPos();
}

void Map::initSprite()
{
    this->_mapSprite.setTexture(this->_mapTexture);
}

void Map::initTexture()
{
    this->_mapTexture.loadFromFile("assets/map/Map1.png");
}

std::vector<sf::RectangleShape> initColisionVolcanoMap()
{
    std::vector<sf::RectangleShape> colision = std::vector<sf::RectangleShape>();
    int x[] = {95, 448, 805, 1161, 1528};
    int y[] = {362, 575, 788, 575, 362};
    int width = 297;
    int height = 21;

    for (size_t i = 0; i < 5; i++) {
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setPosition(x[i], y[i]);
        rect.setFillColor(sf::Color::Red);
        colision.push_back(rect);
    }
    return colision;
}

void Map::initColision(MapType type)
{
    if (type == MapType::VOLCANO) {
        this->_colision = initColisionVolcanoMap();
    } else
        this->_colision = initColisionVolcanoMap();
    this->_nbCollisionShape = this->_colision.size();

}

void Map::initPos()
{
    this->_mapSprite.setPosition(0, 0);
}
