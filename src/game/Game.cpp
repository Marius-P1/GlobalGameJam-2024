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
    delete this->_player1;
    delete this->_player2;
    delete this->_map;
    delete this->_player1Life;
    delete this->_player2Life;
}

void Game::handleEvent(sf::Event event)
{
    this->_player1->handleEvent(event, this->_map);
    this->_player2->handleEvent(event, this->_map);
    if (sf::Keyboard::isKeyPressed(this->_player1->getAttackKey())) {
        this->_nbPlayer2Life = this->_player1->useAttack(this->_player2);
    }
    if (sf::Keyboard::isKeyPressed(this->_player2->getAttackKey())) {
        this->_nbPlayer2Life = this->_player2->useAttack(this->_player1);
    }
    if (sf::Keyboard::isKeyPressed(this->_player1->getSpecial()) && this->_player1PigeonType != PigeonType::THIN_PIGEON) {
        this->_player2Life = this->_player1->useSpecial(this->_player2);
    }
    if (sf::Keyboard::isKeyPressed(this->_player2->getSpecial()) && this->_player2PigeonType != PigeonType::THIN_PIGEON) {
        this->_nbPlayer1Life = this->_player2->useSpecial(this->_player1);
    }
    this->_nbPlayer2Life = this->_player1->makeDamage(this->_player2);
    this->_nbPlayer1Life = this->_player2->makeDamage(this->_player1);

    if (this->_nbPlayerAlive == 0 || this->_nbPlayer2Life == 0) {
        this->_nbPlayerAlive--;
        if (this->_nbPlayerAlive == 0) {
            std::cout << "Player 2 win" << std::endl;
        } else {
            std::cout << "Player 1 win" << std::endl;
        }
    }
}

void Game::update()
{
    this->_player1->update(this->_map);
    this->_player2->update(this->_map);
    if (isFallen(this->_player1)) {
        this->_player1->respawn(this->_map->getSpawnPos());
        this->_nbPlayer1Life--;
    }
    if (isFallen(this->_player2)) {
        this->_player2->respawn(this->_map->getSpawnPos());
        this->_nbPlayer2Life--;
    }
    this->_player1Life->setLife(this->_nbPlayer1Life);
    this->_player2Life->setLife(this->_nbPlayer2Life);
}

void Game::draw(sf::RenderWindow &window)
{
    this->_map->draw(window);

    this->_player1->draw(window);
    this->_player2->draw(window);
    this->_player1Life->draw(window);
    this->_player2Life->draw(window);
}

bool Game::isFallen(Player *player)
{
    if (player->getPos().y > 1080) {
        return true;
    }
    return false;
}

void Game::init()
{
    randomGameParam();
    this->_map = new Map(this->_mapType);
    this->_player1 = new Player(PlayerType::PLAYER1, this->_player1PigeonType, this->_map->getSpawnPos());
    this->_player2 = new Player(PlayerType::PLAYER2, this->_player2PigeonType, this->_map->getSpawnPos());
    this->_nbPlayerAlive = 2;
    this->_nbPlayer1Life = 3;
    this->_nbPlayer2Life = 3;
    this->_player1Life = new Life(PlayerType::PLAYER1, this->_player1PigeonType);
    this->_player2Life = new Life(PlayerType::PLAYER2, this->_player2PigeonType);
}

void Game::randomGameParam()
{
    time_t t;
    std::srand(static_cast<unsigned int>(time(&t)));

    this->_mapType = static_cast<MapType>(std::rand() % 4);
    this->_player1PigeonType = static_cast<PigeonType>(std::rand() % 4);
    this->_player2PigeonType = static_cast<PigeonType>(std::rand() % 4);
}
