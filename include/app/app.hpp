/*
** EPITECH PROJECT, 2024
** GJ
** File description:
** app
*/

#pragma once

#include <SFML/Graphics.hpp>

class App {
    public:
        void run();
    private:
    sf::RenderWindow _window;

};

class player {
    public:
        void run();
    private:
    sf::RectangleShape _rect;

};

class map{
    public:
        void run();
    private:
    sf::RectangleShape _bot;

};


