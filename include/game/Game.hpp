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
        bool isColliding();

    private:
        void init();
        void clean();

        Player *_player;
        Map *_map;

};