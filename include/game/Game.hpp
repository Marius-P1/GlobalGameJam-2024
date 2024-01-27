/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** game
*/

#pragma once

#include "../include.hpp"
#include "../player/Player.hpp"
#include "../map/Map.hpp"

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
        Player *_player2;
        PigeonType _player2PigeonType;
        Map *_map;
        MapType _mapType;
        int _nbPlayerAlive;
        int _player1Life;
        int _player2Life;

};