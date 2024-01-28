/*
** EPITECH PROJECT, 2024
** GJ
** File description:
** Init
*/

#include "./player/Player.hpp"

void Player::init(PlayerType numberOfThePlayer, PigeonType pigeonType, sf::Vector2f spawnPos)
{
    initPos(spawnPos);
    initVariables(pigeonType);

    switch (pigeonType) {
        case PigeonType::FAT_PIGEON :
            initFatPigeon();
            break;
        case PigeonType::SMALL_PIGEON :
            initSmallPigeon();
            break;
        case PigeonType::THIN_PIGEON :
            initThinPigeon();
            break;
        case PigeonType::MUSCULAR_PIGEON :
            initMuscularPigeon();
            break;
        default:
            initThinPigeon();
            break;
    }
    initAttackColision(ATTACK_RANGE);
    initTouch(numberOfThePlayer);
}

void Player::initTouch(PlayerType numberOfThePlayer)
{
    if (numberOfThePlayer == PlayerType::PLAYER1) {
        this->_right = sf::Keyboard::D;
        this->_left = sf::Keyboard::Q;
        this->_up = sf::Keyboard::Z;
        this->_attack = sf::Keyboard::E;
        this->_special = sf::Keyboard::A;
        this->_jump = sf::Keyboard::Space;
        this->_displayColision = sf::Keyboard::K;
    } else {
        this->_right = sf::Keyboard::Right;
        this->_left = sf::Keyboard::Left;
        this->_up = sf::Keyboard::Up;
        this->_attack = sf::Keyboard::Numpad0;
        this->_special = sf::Keyboard::Numpad2;
        this->_jump = sf::Keyboard::Numpad1;
        this->_displayColision = sf::Keyboard::Add;
    }
}

void Player::initSprite(std::vector<int> array)
{
    this->_spriteSheet = new SpriteSheetSimplifier(8, 120, 180, array);
    sf::Sprite sprite(_playerTexture, this->_spriteSheet->animate(IDLEL));
    this->_player = sprite;
}

void Player::initTexture(std::string path)
{
    this->_playerTexture.loadFromFile(path);
}

void Player::initVariables(PigeonType pigeonType)
{
    this->_type = pigeonType;
    this->_oldPlayerPos = this->_playerPos;
    this->lookingRight = true;
    this->isAttacking = false;
    this->isSpecial = false;
    this->displayColision = false;
    this->_isJumping = JumpType::NOJUMP;
    this->_gravity = 0.01f;
    this->_jumpForce = -7.f;
    this->_velocity = {0,0};
    this->_acceleration = {0,0};
    this->_nbLife = 3;
    this->_isFly = true;
    this->_attackClock.restart();
    this->_damageClock.restart();
    this->_respawnClock.restart();
}

void Player::initPos(sf::Vector2f spawnPos)
{
    this->_playerPos = spawnPos;
    this->_player.setPosition(this->_playerPos);
}

void Player::initAttackColision(size_t reachSize)
{
    this->reachSize = reachSize;
    this->_playerAttackColision = sf::RectangleShape(sf::Vector2f(this->reachSize, this->_player.getGlobalBounds().height));
    this->_playerAttackColision.setFillColor(sf::Color::Red);
}

void Player::updateColision()
{
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 173.f;
    this->_playerColision.setPosition(pos);
    updateAttackColision();
}

void Player::initFatPigeon()
{
    initTexture("assets/player/fatPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 5, 5, 3, 3};
    this->_canDoDJump = false;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(69.f, 173.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 173.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(3);
}

void Player::updateTextureRect()
{
    this->_player.setTextureRect(this->_spriteSheet->animate(this->_anim));
}

void Player::initSmallPigeon()
{
    initTexture("assets/player/smallPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 4, 4, 5, 5};
    this->_canDoDJump = false;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(69.f, 173.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 173.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(3);
}

void Player::initThinPigeon()
{
    initTexture("assets/player/thinPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 3, 3, 4, 4};
    this->_canDoDJump = true;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(69.f, 173.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 173.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(3);
}

void Player::initMuscularPigeon()
{
    initTexture("assets/player/muscularPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 5, 5, 5, 5};
    this->_canDoDJump = false;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(69.f, 173.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 173.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(3);
}
