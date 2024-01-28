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

bool Game::menuButtonHandling(sf::Event event)
{
    if (this->_buttonShape.getGlobalBounds().contains(sf::Vector2f(sf::Mouse::getPosition()))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->_buttonState = ButtonState::CLICK;
        } else {
            this->_buttonState = ButtonState::HOVER;
        }
        if (this->_isClicked && event.type == sf::Event::MouseButtonReleased) {
            this->_isClicked = false;
            return true;
        }
    } else {
        if (event.type == sf::Event::MouseButtonReleased)
            this->_isClicked = false;
        this->_buttonState = ButtonState::IDLE;
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->_isClicked = true;
    return false;
}

SceneType Game::handleEvent(sf::Event event)
{
    if (this->_nbPlayer1Life == 0 || this->_nbPlayer2Life == 0) {
        if (menuButtonHandling(event))
            return SceneType::MENU;
        else
            return SceneType::GAME;
    }
    this->_player1->handleEvent(event, this->_map);
    this->_player2->handleEvent(event, this->_map);
    if (sf::Keyboard::isKeyPressed(this->_player1->getAttackKey())) {
        this->_nbPlayer2Life = this->_player1->useAttack(this->_player2);
    }
    if (sf::Keyboard::isKeyPressed(this->_player2->getAttackKey())) {
        this->_nbPlayer1Life = this->_player2->useAttack(this->_player1);
    }
    return SceneType::GAME;
}

void Game::updateMenuButton()
{
    if (this->_buttonState == ButtonState::IDLE) {
        this->_buttonRect.top = 0;
    } else if (this->_buttonState == ButtonState::HOVER) {
        this->_buttonRect.top = 85;
    } else if (this->_buttonState == ButtonState::CLICK) {
        this->_buttonRect.top = 170;
    }
    this->_buttonShape.setTextureRect(this->_buttonRect);
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
    updateMenuButton();
    if (this->_nbPlayer1Life == 0 || this->_nbPlayer2Life == 0) {
        if (!this->_isSoundPlayed) {
            this->_sound.play();
            this->_isSoundPlayed = true;
        }
    }
}

void Game::drawnWin(sf::RenderWindow &window, Player *player)
{
    std::string path = player->getPathWinTexture();

    if (this->_isAnimated && this->_clock.getElapsedTime().asSeconds() > 0.1) {
        if (this->_winTexture.loadFromFile(path + std::to_string(this->_indexWinTexture) + ".jpg")) {
            this->_winSprite.setTexture(this->_winTexture);
        } else {
            this->_isAnimated = false;
        }
        this->_clock.restart();
        this->_indexWinTexture++;
    }
    this->_winSprite.setPosition(0, 0);
    this->_winSprite.setTexture(this->_winTexture);
    window.draw(this->_winSprite);
    window.draw(this->_buttonShape);

}

void Game::draw(sf::RenderWindow &window)
{
    this->_map->draw(window);

    this->_player1->draw(window);
    this->_player2->draw(window);
    this->_player1Life->draw(window);
    this->_player2Life->draw(window);
    if (this->_nbPlayer1Life == 0) {
        drawnWin(window, this->_player2);
    }
    if (this->_nbPlayer2Life == 0) {
        drawnWin(window, this->_player1);
    }
}

bool Game::isFallen(Player *player)
{
    if (player->getPos().y > 1080) {
        return true;
    }
    return false;
}

void Game::initButton()
{
    this->_buttonState = ButtonState::IDLE;
    this->_buttonRect = sf::IntRect(0, 0, 213, 85);
    this->_buttonPos = sf::Vector2f(740, 880);
    this->_buttonTexture.loadFromFile("./assets/button_menu.png");
    this->_buttonShape.setSize(sf::Vector2f(440, 130));
    this->_buttonShape.setPosition(this->_buttonPos);
    this->_buttonShape.setTexture(&this->_buttonTexture);
    this->_isClicked = false;
}

void Game::init()
{
    randomGameParam();
    initButton();
    this->_map = new Map(this->_mapType);
    this->_player1 = new Player(PlayerType::PLAYER1, this->_player1PigeonType, this->_map->getSpawnPos());
    this->_player2 = new Player(PlayerType::PLAYER2, this->_player2PigeonType, this->_map->getSpawnPos());
    this->_nbPlayerAlive = 2;
    this->_nbPlayer1Life = 3;
    this->_nbPlayer2Life = 3;
    this->_player1Life = new Life(PlayerType::PLAYER1, this->_player1PigeonType);
    this->_player2Life = new Life(PlayerType::PLAYER2, this->_player2PigeonType);
    this->_indexWinTexture = 1;
    this->_clock.restart();
    this->_isAnimated = true;
    this->_buffer.loadFromFile("./assets/sound/win.ogg");
    this->_sound.setBuffer(this->_buffer);
    this->_sound.setVolume(50);
    this->_isSoundPlayed = false;
}

void Game::randomGameParam()
{
    time_t t;
    std::srand(static_cast<unsigned int>(time(&t)));

    this->_mapType = static_cast<MapType>(std::rand() % 4);
    this->_player1PigeonType = static_cast<PigeonType>(std::rand() % 4);
    this->_player2PigeonType = static_cast<PigeonType>(std::rand() % 4);
}
