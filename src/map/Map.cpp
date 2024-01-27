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

sf::Vector2f Map::getSpawnPos()
{
    if (this->_indexSpawnPos >= this->_spawnPos.size()) {
        this->_indexSpawnPos = 0;
    }
    this->_lastSpawnPos = this->_spawnPos[this->_indexSpawnPos];
    this->_indexSpawnPos++;
    return this->_lastSpawnPos;
}

void Map::init(MapType type)
{
    switch (type) {
        case MapType::VOLCANO :
            initMapVolcano();
            break;
        case MapType::JUNGLE :
            initMapJungle();
            break;
        case MapType::SNOW :
            initMapSnow();
            break;
        case MapType::SKY :
            initMapSky();
            break;
        default:
            initMapVolcano();
            break;
    }
    this->_nbCollisionShape = this->_colision.size();
    this->_indexSpawnPos = 0;
    this->_lastSpawnPos = sf::Vector2f(0, 0);
    initPos();
}

void Map::initSprite()
{
    this->_mapSprite.setTexture(this->_mapTexture);
}

void Map::initTexture(std::string path)
{
    this->_mapTexture.loadFromFile(path);
}

void Map::initPos()
{
    this->_mapSprite.setPosition(0, 0);
}

/*        INITIALISATION MAP VOLCANO        */

std::vector<sf::RectangleShape> initColisionVolcanoMap()
{
    std::vector<sf::RectangleShape> colision = std::vector<sf::RectangleShape>();
    int x[] = {94, 442, 797, 1152, 1507};
    int y[] = {358, 565, 775, 567, 346};
    int width = 316;
    int height = 52;

    for (size_t i = 0; i < 5; i++) {
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setPosition(x[i], y[i]);
        rect.setFillColor(sf::Color::Red);
        colision.push_back(rect);
    }
    return colision;
}

std::vector<sf::Vector2f> initSpawnPosVolcanoMap()
{
    std::vector<sf::Vector2f> spawnPos = std::vector<sf::Vector2f>();
    int x[] = {200, 1650, 900};
    int y[] = {80, 80, 250};

    for (size_t i = 0; i < 3; i++) {
        sf::Vector2f pos = sf::Vector2f(x[i], y[i]);
        spawnPos.push_back(pos);
    }
    return spawnPos;
}

void Map::initMapVolcano()
{
    initTexture("assets/map/volcano.png");
    initSprite();
    this->_colision = initColisionVolcanoMap();
    this->_spawnPos = initSpawnPosVolcanoMap();
}

/*        INITIALISATION MAP JUNGLE        */


std::vector<sf::RectangleShape> initColisionMapJungle()
{
    std::vector<sf::RectangleShape> colision = std::vector<sf::RectangleShape>();
    int x[] = {103, 1185};
    int y[] = {439, 612};
    int width = 651;
    int height = 68;

    for (size_t i = 0; i < 2; i++) {
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width, height));
        rect.setPosition(x[i], y[i]);
        rect.setFillColor(sf::Color::Red);
        colision.push_back(rect);
    }
    return colision;
}

std::vector<sf::Vector2f> initSpawnPosMapJungle()
{
    std::vector<sf::Vector2f> spawnPos = std::vector<sf::Vector2f>();
    int x[] = {200, 1720, 620, 1300};
    int y[] = {120, 250, 120, 250};

    for (size_t i = 0; i < 4; i++) {
        sf::Vector2f pos = sf::Vector2f(x[i], y[i]);
        spawnPos.push_back(pos);
    }
    return spawnPos;
}

void Map::initMapJungle()
{
    initTexture("assets/map/jungle.png");
    initSprite();
    this->_colision = initColisionMapJungle();
    this->_spawnPos = initSpawnPosMapJungle();
}

/*        INITIALISATION MAP SNOW        */


std::vector<sf::RectangleShape> initColisionMapSnow()
{
    std::vector<sf::RectangleShape> colision = std::vector<sf::RectangleShape>();
    int x[] = {606, 236};
    int y[] = {446, 847};
    int width[] = {663, 1489};
    int height[] = {83, 250};

    for (size_t i = 0; i < 2; i++) {
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width[i], height[i]));
        rect.setPosition(x[i], y[i]);
        rect.setFillColor(sf::Color::Red);
        colision.push_back(rect);
    }
    return colision;
}

std::vector<sf::Vector2f> initSpawnPosMapSnow()
{
    std::vector<sf::Vector2f> spawnPos = std::vector<sf::Vector2f>();
    int x[] = {350, 1400, 850};
    int y[] = {220, 220, 100};

    for (size_t i = 0; i < 3; i++) {
        sf::Vector2f pos = sf::Vector2f(x[i], y[i]);
        spawnPos.push_back(pos);
    }
    return spawnPos;
}

void Map::initMapSnow()
{
    initTexture("assets/map/snow.png");
    initSprite();
    this->_colision = initColisionMapSnow();
    this->_spawnPos = initSpawnPosMapSnow();
}

/*        INITIALISATION MAP SKY        */


std::vector<sf::RectangleShape> initColisionMapSky()
{
    std::vector<sf::RectangleShape> colision = std::vector<sf::RectangleShape>();
    int x[] = {125, 713, 1401};
    int y[] = {520, 673, 412};
    int width[] = {442, 600, 442};
    int height[] = {56, 83, 56};

    for (size_t i = 0; i < 3; i++) {
        sf::RectangleShape rect = sf::RectangleShape(sf::Vector2f(width[i], height[i]));
        rect.setPosition(x[i], y[i]);
        rect.setFillColor(sf::Color::Red);
        colision.push_back(rect);
    }
    return colision;
}

std::vector<sf::Vector2f> initSpawnPosMapSky()
{
    std::vector<sf::Vector2f> spawnPos = std::vector<sf::Vector2f>();
    int x[] = {290, 1530, 900};
    int y[] = {120, 85, 250};

    for (size_t i = 0; i < 3; i++) {
        sf::Vector2f pos = sf::Vector2f(x[i], y[i]);
        spawnPos.push_back(pos);
    }
    return spawnPos;
}

void Map::initMapSky()
{
    initTexture("assets/map/sky.png");
    initSprite();
    this->_colision = initColisionMapSky();
    this->_spawnPos = initSpawnPosMapSky();
}
