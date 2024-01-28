/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Menu
*/

#pragma once

#include "./include.hpp"
#include "./enum/enum.hpp"

class Menu {
    public:
        Menu();
        ~Menu();
        SceneType handleEvent(sf::Event event);
        void update();
        void draw(sf::RenderWindow &window);
        void resetMenu();

    private:
        void init();
        void initButtons();

        bool _isAnimated;
        size_t _index;
        bool _isClicked;
        ButtonState _buttonState;
        sf::IntRect _buttonRect;
        sf::RectangleShape _buttonShape;
        sf::Vector2f _buttonPos;
        sf::Texture _buttonTexture;
        sf::Texture _backgroundTexture;
        sf::Sprite _background;
        sf::Clock _clock;
        sf::SoundBuffer _buffer;
        sf::Sound _sound;
        bool _isSoundPlayed;

};
