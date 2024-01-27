/*
** EPITECH PROJECT, 2024
** GJ
** File description:
** app
*/

#pragma once

#include "./game/Game.hpp"

class App {
    public:
        App();
        ~App();

    private:
        void run();
        void handleEvent();
        void update();
        void draw();
        void init();
        void clean();

        bool _isRunning;
        sf::Event _event;
        sf::RenderWindow _window;
        Game *_game;

};

class map{
    public:
        void run();
    private:
    sf::RectangleShape _bot;

};


