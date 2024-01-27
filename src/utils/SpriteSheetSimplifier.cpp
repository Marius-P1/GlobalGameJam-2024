/*
** EPITECH PROJECT, 2024
** GJ_2
** File description:
** SpriteSheetSimplifier
*/

#include "./utils/SpriteSheetSimplifier.hpp"

SpriteSheetSimplifier::SpriteSheetSimplifier(int nbLigne, int x, int y, std::vector<int> array)
{
    this->_nbLigne = nbLigne;
    this->_width = x;
    this->_height = y;
    this->_array = array;
    this->_index = 0;
    this->_anim = 0;
    this->_nbSprites = 0;
}

SpriteSheetSimplifier::~SpriteSheetSimplifier()
{
}

void SpriteSheetSimplifier::updateRect()
{
    this->_rect.top = _height * _anim;
    this->_rect.width = _width;
    this->_rect.height = _height;
}

void SpriteSheetSimplifier::updateAnim()
{
    if (this->_time.getElapsedTime().asMilliseconds() > 100) {
        _index++;
        if (this->_index >= this->_nbSprites)
            this->_index = 0;
        this->_rect.left = this->_width * this->_index;
        this->_time.restart();
    }
}

sf::IntRect SpriteSheetSimplifier::animate(int anim)
{
    this->_nbSprites = this->_array[anim];
    if (anim == this->_anim)
        updateAnim();
    else {
        this->_anim = anim;
        this->_rect.left = 0;
        this->_index = 0;
        updateRect();
    }

    return this->_rect;
}

