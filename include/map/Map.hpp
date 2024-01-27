/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Map
*/

#pragma once

#include "./include.hpp"
#include "./enum/enum.hpp"

class Map {
    public:
        Map(MapType type = MapType::VOLCANO);
        ~Map();
        void draw(sf::RenderWindow &window);
        std::vector<sf::RectangleShape> getColision();
        size_t getNbCollisionShape();

    private:
        void init(MapType type);
        void initSprite();
        void initTexture();
        void initColision(MapType type);
        void initPos();

        sf::Sprite _mapSprite;
        sf::Texture _mapTexture;
        std::vector<sf::RectangleShape> _colision;
        size_t _nbCollisionShape;

};
