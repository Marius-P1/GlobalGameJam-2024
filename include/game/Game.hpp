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

        Player *_player1;
        Player *_player2;
        Map *_map;

};