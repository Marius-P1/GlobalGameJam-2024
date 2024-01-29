/*
** EPITECH PROJECT, 2024
** GJ
** File description:
** app
*/

#include "./app/App.hpp"

App::App()
{
    init();
    run();
}

App::~App()
{
    clean();
}

void App::init()
{
    auto image = sf::Image{};
    image.loadFromFile("./assets/icon.png");
    this->_isRunning = true;
    this->_window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());
    this->_window.create(sf::VideoMode(1920, 1080), "Sucker Fighter", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_game = new Game();
    this->_menu = new Menu();
    this->_sceneType = MENU;
    std::srand(time(NULL));
}

void App::run()
{
    while (this->_isRunning) {
        switch (this->_sceneType) {
            case MENU:
                runMenu();
                break;
            case GAME:
                runGame();
                break;
            default:
                break;
        }
    }
}

void App::runMenu()
{
    handleEventMenu();
    updateMenu();
    drawMenu();
}

void App::handleEventMenu()
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_isRunning = false;
    }
    this->_sceneType = this->_menu->handleEvent(this->_event);
}

void App::updateMenu()
{
    this->_menu->update();
}

void App::drawMenu()
{
    this->_window.clear(sf::Color::Black);
    this->_menu->draw(this->_window);
    this->_window.display();
}

void App::runGame()
{
    handleEventGame();
    updateGame();
    drawGame();
    if (this->_sceneType == MENU) {
        this->_menu->resetMenu();
        resetGame();
    }
}

void App::handleEventGame()
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_isRunning = false;
    }
    this->_sceneType = this->_game->handleEvent(this->_event);
}

void App::updateGame()
{
    this->_game->update();
}

void App::drawGame()
{
    this->_window.clear(sf::Color::Black);
    this->_game->draw(this->_window);
    this->_window.display();
}

void App::resetGame()
{
    delete this->_game;
    this->_game = new Game();
}

void App::clean()
{
    this->_window.close();
    delete this->_game;
}