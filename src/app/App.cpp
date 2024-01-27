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
    this->_isRunning = true;
    this->_window.create(sf::VideoMode(1920, 1080), "GJ", sf::Style::Fullscreen);
    this->_window.setFramerateLimit(60);
    this->_game = new Game();
}

void App::run()
{
    while (this->_isRunning) {
        handleEvent();
        update();
        draw();
    }
}

void App::handleEvent()
{
    while (this->_window.pollEvent(this->_event)) {
        if (this->_event.type == sf::Event::Closed)
            this->_isRunning = false;
        this->_game->handleEvent(this->_event);
    }
}

void App::update()
{
    this->_game->update();
}

void App::draw()
{
    this->_window.clear(sf::Color::Black);
    this->_game->draw(this->_window);
    this->_window.display();
}

void App::clean()
{
    this->_window.close();
}