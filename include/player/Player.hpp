/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** player
*/

#pragma once

#include "../include.hpp"
#include "./enum/enum.hpp"
#include "./map/Map.hpp"
#include "./utils/SpriteSheetSimplifier.hpp"

class Player {
    public:
        Player(PlayerType type, PigeonType pigeonType, sf::Vector2f spawnPos);
        ~Player();
        void handleEvent(sf::Event event, Map *map);
        void update(Map *map);
        void draw(sf::RenderWindow &window);
        void move(sf::Vector2f move, Map *map);
        void setPlayerPos(sf::Vector2f pos);
        sf::Vector2f getOldPlayerPos() const;
        void displayColisionHitBox(sf::RenderWindow &window);
        void resetJump();
        void stateFly(bool state);
        void jump();
        int useAttack(Player *player);
        sf::Keyboard::Key getAttackKey() const;
        void respawn(sf::Vector2f spawnPos);
        sf::Vector2f getPos() const;

    private:
        void init(PlayerType type, PigeonType pigeonType, sf::Vector2f spawnPos);
        void initSprite();
        void initTexture(std::string path);
        void initVariables();
        void initPos(sf::Vector2f spawnPos);
        void initAttackColision(size_t reachSize);
        void updateColision();
        void updateAttackColision();
        void updateTextureRect();
        bool isColliding(Map *map);
        void initFatPigeon();
        void initSmallPigeon();
        void initThinPigeon();
        void initMuscularPigeon();
        void initTouch(PlayerType numberOfThePlayer);

        sf::Sprite _player;
        SpriteSheetSimplifier *_spriteSheet;
        PlayerAnimation _anim = IDLER;
        sf::Clock _clock;
        sf::IntRect _rect;
        sf::Texture _playerTexture;
        sf::Vector2f _playerPos;
        sf::Vector2f _oldPlayerPos;
        sf::Vector2f _velocity;
        sf::Vector2f _acceleration;
        sf::RectangleShape _playerColision;
        sf::RectangleShape _playerAttackColision;
        size_t reachSize;
        bool lookingRight;
        bool isAttacking;
        bool displayColision;
        float _gravity;
        bool _isFly;
        float _jumpForce;
        int _nbLife;
        sf::Clock _attackClock;
        sf::Clock _damageClock;
        sf::Clock _respawnClock;
        JumpType _isJumping;
        sf::Keyboard::Key _right;
        sf::Keyboard::Key _left;
        sf::Keyboard::Key _up;
        sf::Keyboard::Key _attack;
        sf::Keyboard::Key _jump;
        sf::Keyboard::Key _displayColision;

};
