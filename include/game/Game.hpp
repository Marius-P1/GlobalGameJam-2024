/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** game
*/

#pragma once

#include "./include.hpp"
#include "./player/Player.hpp"
#include "./map/Map.hpp"
#include "./player/Life.hpp"

class Game {
    public:
        Game();
        ~Game();
        void handleEvent(sf::Event event);
        void update();
        void draw(sf::RenderWindow &window);
        bool isColliding(Player *player);

    private:
        void init();
        void clean();
        bool isFallen(Player *player);
        void randomGameParam();

        Player *_player1;
        PigeonType _player1PigeonType;
        Life *_player1Life;
        Player *_player2;
        PigeonType _player2PigeonType;
        Life *_player2Life;
        Map *_map;
        MapType _mapType;
        int _nbPlayerAlive;
        int _nbPlayer1Life;
        int _nbPlayer2Life;

};