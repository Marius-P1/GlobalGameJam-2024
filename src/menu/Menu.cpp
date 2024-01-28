/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Menu
*/

#include "./menu/Menu.hpp"

Menu::Menu()
{
    init();
}

Menu::~Menu()
{
}

SceneType Menu::handleEvent(sf::Event event)
{
    (void)event;
    if (this->_buttonShape.getGlobalBounds().contains(
        sf::Vector2f(sf::Mouse::getPosition()))) {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            this->_buttonState = ButtonState::CLICK;
        } else {
            this->_buttonState = ButtonState::HOVER;
        }
        if (this->_isClicked && event.type == sf::Event::MouseButtonReleased) {
            this->_isClicked = false;
            this->_sound.stop();
            return SceneType::GAME;
        }
    } else {
        if (event.type == sf::Event::MouseButtonReleased)
            this->_isClicked = false;
        this->_buttonState = ButtonState::IDLE;
    }
    if (this->_isAnimated) {
        if (this->_clock.getElapsedTime().asSeconds() > 0.1) {
            if (this->_backgroundTexture.loadFromFile(
                "./assets/menu/menu" + std::to_string(this->_index) + ".png")) {
                this->_background.setTexture(this->_backgroundTexture);
            } else {
                this->_isAnimated = false;
            }
            this->_clock.restart();
            this->_index++;
        }
    }
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        this->_isClicked = true;
    return SceneType::MENU;
}

void Menu::update()
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

void Menu::draw(sf::RenderWindow &window)
{
    if (!this->_isSoundPlayed) {
        this->_sound.play();
        this->_isSoundPlayed = true;
    }
    window.draw(this->_background);
    window.draw(this->_buttonShape);
}

void Menu::resetMenu()
{
    init();
}

void Menu::init()
{
    initButtons();
    this->_isAnimated = true;
    this->_index = 0;
    this->_clock.restart();
    this->_backgroundTexture.loadFromFile("./assets/menu/menu0.png");
    this->_background.setTexture(this->_backgroundTexture);
    this->_isClicked = false;
    this->_isSoundPlayed = false;
    this->_buffer.loadFromFile("./assets/sound/menu.ogg");
    this->_sound.setBuffer(this->_buffer);
    this->_sound.setVolume(50);
    this->_sound.setLoop(true);
}

void Menu::initButtons()
{
    this->_buttonState = ButtonState::IDLE;
    this->_buttonRect = sf::IntRect(0, 0, 213, 85);
    this->_buttonPos = sf::Vector2f(600, 840);
    this->_buttonTexture.loadFromFile("./assets/menu/button_play.png");
    this->_buttonShape.setSize(sf::Vector2f(660, 195));
    this->_buttonShape.setPosition(this->_buttonPos);
    this->_buttonShape.setTexture(&this->_buttonTexture);
}
