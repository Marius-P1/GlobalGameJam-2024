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
        void drawShield(sf::RenderWindow &window);
        void move(sf::Vector2f move, Map *map);
        void setPlayerPos(sf::Vector2f pos);
        sf::Vector2f getOldPlayerPos() const;
        void displayColisionHitBox(sf::RenderWindow &window);
        void resetJump();
        void stateFly(bool state);
        sf::FloatRect getBound();
        void jump();
        int useAttack(Player *player);
        int useSpecial(Player *player);
        int makeDamage(Player *player);
        sf::Keyboard::Key getAttackKey() const;
        sf::Keyboard::Key getSpecial() const;
        void respawn(sf::Vector2f spawnPos);
        sf::Vector2f getPos() const;
        std::string getPathWinTexture() const;

    private:
        void init(PlayerType type, PigeonType pigeonType, sf::Vector2f spawnPos);
        void initSprite(std::vector<int> array);
        void initTexture(std::string path);
        void initVariables(PigeonType pigeonType);
        void initPos(sf::Vector2f spawnPos);
        void initAttackColision(size_t reachSize);
        void initFatPigeon();
        void initSmallPigeon();
        void initThinPigeon();
        void initMuscularPigeon();
        void initTouch(PlayerType numberOfThePlayer);

        void updateSpecialAnimation();
        void updateColision();
        void updateAttackColision();
        void attackResetAnim();
        void updateTextureRect();
        void updateAttackAnimation();
        void makeDash();
        bool isColliding(Map *map);

        sf::Sprite _player;
        Map *_map;
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
        sf::Texture _shieldTexture;
        sf::RectangleShape _shield;
        std::string _pathWinTexture;
        size_t reachSize;
        float _timeAttack;
        float _timeSpecial;
        bool lookingRight;
        bool isAttacking;
        bool isSpecial;
        bool displayColision;
        bool _canDoDJump;
        bool _canSpecial = false;
        float _gravity;
        bool _isFly;
        float _jumpForce;
        int _nbLife;
        int _type;
        float _hitboxHeight;
        float _hitboxWidth;
        sf::Clock _attackClock;
        sf::Clock _damageClock;
        sf::Clock _respawnClock;
        sf::Clock _SpecialClock;
        JumpType _isJumping;
        sf::Keyboard::Key _right;
        sf::Keyboard::Key _left;
        sf::Keyboard::Key _up;
        sf::Keyboard::Key _attack;
        sf::Keyboard::Key _special;
        sf::Keyboard::Key _jump;
        sf::Keyboard::Key _displayColision;
        sf::SoundBuffer _soundBufferAttack;
        sf::Sound _soundAttack;
        sf::SoundBuffer _soundBufferSpecial;
        sf::Sound _soundSpecial;
        sf::SoundBuffer _soundBufferDamage;
        sf::Sound _soundDamage;
        sf::SoundBuffer _soundBufferJump;
        sf::Sound _soundJump;
        sf::SoundBuffer _soundBufferWin;
        sf::Sound _soundWin;


};
