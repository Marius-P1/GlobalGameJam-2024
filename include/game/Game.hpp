/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** game
*/

#pragma once

#include "./include.hpp"
#include "./enum/enum.hpp"
#include "./player/Player.hpp"
#include "./map/Map.hpp"
#include "./player/Life.hpp"

class Game {
    public:
        Game();
        ~Game();
        SceneType handleEvent(sf::Event event);
        void update();
        void draw(sf::RenderWindow &window);
        bool isColliding(Player *player);

    private:
        void init();
        void initButton();
        void clean();
        bool isFallen(Player *player);
        void randomGameParam();
        void drawnWin(sf::RenderWindow &window, Player *player);
        bool menuButtonHandling(sf::Event event);
        void updateMenuButton();

        Player *_player1;
        PigeonType _player1PigeonType;
        Life *_player1Life;
        Player *_player2;
        PigeonType _player2PigeonType;
        Life *_player2Life;
        Map *_map;
        MapType _mapType;
        int _nbPlayerAlive;
        int _nbPlayer1Life;
        int _nbPlayer2Life;
        sf::Sprite _winSprite;
        int _indexWinTexture;
        bool _isAnimated;
        sf::Clock _clock;
        sf::Texture _winTexture;
        ButtonState _buttonState;
        sf::IntRect _buttonRect;
        sf::RectangleShape _buttonShape;
        sf::Vector2f _buttonPos;
        sf::Texture _buttonTexture;
        bool _isClicked;
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
        bool _isSoundPlayed;

};