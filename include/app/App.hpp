/*
** EPITECH PROJECT, 2024
** GJ
** File description:
** app
*/

#pragma once

#include "./game/Game.hpp"
#include "./menu/Menu.hpp"
#include "./include.hpp"
#include "./enum/enum.hpp"

class App {
    public:
        App();
        ~App();

    private:
        void run();
        void runMenu();
        void runGame();
        void handleEventGame();
        void updateGame();
        void drawGame();
        void handleEventMenu();
        void updateMenu();
        void drawMenu();
        void init();
        void clean();
        void resetGame();

        SceneType _sceneType;
        bool _isRunning;
        sf::Event _event;
        sf::RenderWindow _window;
        Game *_game;
        Menu *_menu;

};
