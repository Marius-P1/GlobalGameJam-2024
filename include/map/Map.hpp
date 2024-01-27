/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Map
*/

#pragma once

#include "../include.hpp"

class Map {
    public:
        Map();
        ~Map();
        void draw(sf::RenderWindow &window);
        sf::Image getColisionImage();

    private:
        void init();
        void initSprite();
        void initTexture();
        void initColision();
        void initPos();

        sf::Sprite _mapSprite;
        sf::Texture _mapTexture;
        sf::Image _colisionImage;
        sf::Texture _colisionTexture;

};
