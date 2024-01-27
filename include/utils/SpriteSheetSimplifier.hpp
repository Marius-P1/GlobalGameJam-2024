/*
** EPITECH PROJECT, 2024
** GJ_2
** File description:
** SpriteSheetSimplier
*/

#pragma once
#include "../include.hpp"
#include <iostream>

#include <SFML/Graphics/Rect.hpp>

class SpriteSheetSimplifier {
    public:
        SpriteSheetSimplifier(int nbLigne, int x, int y, std::vector<int> array);
        ~SpriteSheetSimplifier();
        sf::IntRect animate(int anim);

    protected:
    private:
        void updateRect();
        void updateAnim();
        int _nbLigne;
        int _nbSprites;
        int _width;
        int _height;
        std::vector<int> _array;
        int _index;
        int _anim;
        sf::Clock _time;
        sf::IntRect _rect;
};

