/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Life
*/

#include "./player/Life.hpp"

Life::Life(PlayerType playerType, PigeonType pigeonType)
{
    init(pigeonType, playerType);
}

Life::~Life()
{
}

void Life::draw(sf::RenderWindow &window)
{
    switch (this->_life) {
        case 3 :
            window.draw(this->_life3);
            break;
        case 2 :
            window.draw(this->_life2);
            break;
        case 1 :
            window.draw(this->_life1);
            break;
        case 0 :
            window.draw(this->_life0);
            break;
        default:
            window.draw(this->_life0);
            break;
    }
    window.draw(this->_pigeon);
}

void Life::setLife(int life)
{
    this->_life = life;
}

int Life::getLife() const
{
    return this->_life;
}

void Life::init(PigeonType pigeonType, PlayerType playerType)
{
    initLife();
    initPigeon(pigeonType);
    initPos(playerType);
}

void Life::initLife()
{
    this->_life = 3;
    this->_life3Texture.loadFromFile("./assets/player/life3.png");
    this->_life3 = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_life3.setTexture(&this->_life3Texture);
    this->_life2Texture.loadFromFile("./assets/player/life2.png");
    this->_life2 = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_life2.setTexture(&this->_life2Texture);
    this->_life1Texture.loadFromFile("./assets/player/life1.png");
    this->_life1 = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_life1.setTexture(&this->_life1Texture);
    this->_life0Texture.loadFromFile("./assets/player/life0.png");
    this->_life0 = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_life0.setTexture(&this->_life0Texture);
}

void Life::initPigeon(PigeonType pigeonType)
{
    switch (pigeonType) {
        case PigeonType::FAT_PIGEON :
            initFatPigeon();
            break;
        case PigeonType::SMALL_PIGEON :
            initSmallPigeon();
            break;
        case PigeonType::THIN_PIGEON :
            initThinPigeon();
            break;
        case PigeonType::MUSCULAR_PIGEON :
            initMuscularPigeon();
            break;
        default:
            break;
    }
}

void Life::initFatPigeon()
{
    this->_pigeonTexture.loadFromFile("./assets/player/headPigeonFat.png");
    this->_pigeon = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_pigeon.setTexture(&this->_pigeonTexture);
}

void Life::initSmallPigeon()
{
    this->_pigeonTexture.loadFromFile("./assets/player/headPigeonSmall.png");
    this->_pigeon = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_pigeon.setTexture(&this->_pigeonTexture);
}

void Life::initThinPigeon()
{
    this->_pigeonTexture.loadFromFile("./assets/player/headPigeonThin.png");
    this->_pigeon = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_pigeon.setTexture(&this->_pigeonTexture);
}

void Life::initMuscularPigeon()
{
    this->_pigeonTexture.loadFromFile("./assets/player/headPigeonMuscular.png");
    this->_pigeon = sf::RectangleShape(sf::Vector2f(100, 100));
    this->_pigeon.setTexture(&this->_pigeonTexture);
}

void Life::initPos(PlayerType playerType)
{
    switch (playerType) {
        case PlayerType::PLAYER1 :
            this->_lifePos = sf::Vector2f(200, 930);
            this->_pigeonPos = sf::Vector2f(50, 930);
            break;
        case PlayerType::PLAYER2 :
            this->_lifePos = sf::Vector2f(1620, 930);
            this->_pigeonPos = sf::Vector2f(1770, 930);
            break;
        default:
            break;
    }
    this->_life3.setPosition(this->_lifePos);
    this->_life2.setPosition(this->_lifePos);
    this->_life1.setPosition(this->_lifePos);
    this->_life0.setPosition(this->_lifePos);
    this->_pigeon.setPosition(this->_pigeonPos);
}
