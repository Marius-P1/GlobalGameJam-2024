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
        sf::Vector2f getSpawnPos();

    private:
        void init(MapType type);
        void initSprite();
        void initTexture(std::string path);
        void initPos();
        void initMapVolcano();
        void initMapJungle();
        void initMapSnow();
        void initMapSky();

        sf::Sprite _mapSprite;
        sf::Texture _mapTexture;
        std::vector<sf::RectangleShape> _colision;
        size_t _nbCollisionShape;
        std::vector<sf::Vector2f> _spawnPos;
        size_t _indexSpawnPos;
        sf::Vector2f _lastSpawnPos;

};
