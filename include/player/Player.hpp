/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** player
*/

#pragma once

#include "../include.hpp"

class Player {
    public:
        Player();
        ~Player();
        void handleEvent(sf::Event event);
        void update();
        void draw(sf::RenderWindow &window);
        void move(sf::Vector2f move);
        void setPlayerPos(sf::Vector2f pos);
        std::vector<sf::Vector2f> getColisionPoints();
        sf::Vector2f getOldPlayerPos() const;

    private:
        void init();
        void initSprite();
        void initTexture();
        void initPos();
        void initOrigin();
        void initSpeed();
        void clean();

        sf::Sprite _player;
        sf::Texture _playerTexture;
        sf::Vector2f _playerPos;
        sf::Vector2f _oldPlayerPos;
        sf::Vector2f _playerOrigin;
        sf::Vector2f _playerSpeed;

};