/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Life
*/

#pragma once

#include "./include.hpp"
#include "./enum/enum.hpp"
#include "./utils/SpriteSheetSimplifier.hpp"

class Life {
    public:
        Life(PlayerType playerType, PigeonType pigeonType);
        ~Life();
        void draw(sf::RenderWindow &window);
        void setLife(int life);
        int getLife() const;

    private:
        void init(PigeonType pigeonType, PlayerType playerType);
        void initLife();
        void initPigeon(PigeonType pigeonType);
        void initPos(PlayerType playerType);
        void initFatPigeon();
        void initSmallPigeon();
        void initThinPigeon();
        void initMuscularPigeon();

        int _life;
        sf::RectangleShape _life3;
        sf::RectangleShape _life2;
        sf::RectangleShape _life1;
        sf::RectangleShape _life0;
        sf::Texture _life3Texture;
        sf::Texture _life2Texture;
        sf::Texture _life1Texture;
        sf::Texture _life0Texture;
        sf::Vector2f _lifePos;

        sf::RectangleShape _pigeon;
        sf::Texture _pigeonTexture;
        sf::Vector2f _pigeonPos;

};
