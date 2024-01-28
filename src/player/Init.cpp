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
    this->_soundBufferDamage.loadFromFile("assets/sound/damage.ogg");
    this->_soundDamage.setBuffer(this->_soundBufferDamage);
    this->_soundDamage.setVolume(50);
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
    this->_shieldTexture.loadFromFile("assets/player/shield.png");
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
    pos.y += this->_player.getGlobalBounds().height - this->_hitboxHeight;
    pos.x += this->_hitboxWidth;
    this->_playerColision.setPosition(pos);
    updateAttackColision();
}

void Player::initFatPigeon()
{
    initTexture("assets/player/fatPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 5, 5, 3, 3};
    this->_canDoDJump = false;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(87.f, 144.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 144.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setFillColor(sf::Color::Transparent);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(2);
    this->_hitboxHeight = 144.f;
    this->_hitboxWidth = 0.f;
    this->_shield = sf::RectangleShape(sf::Vector2f(80, 80));
    this->_shield.setTexture(&this->_shieldTexture);
    this->_pathWinTexture = "assets/player/FatWin/ezgif-frame-";
    this->_soundBufferAttack.loadFromFile("assets/sound/fatAttack.ogg");
    this->_soundAttack.setBuffer(this->_soundBufferAttack);
    this->_soundAttack.setVolume(50);
    this->_soundBufferSpecial.loadFromFile("assets/sound/fatSpecial.ogg");
    this->_soundSpecial.setBuffer(this->_soundBufferSpecial);
    this->_soundSpecial.setVolume(50);
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

    this->_playerColision = sf::RectangleShape(sf::Vector2f(75.f, 105.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 105.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setFillColor(sf::Color::Transparent);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(2);
    this->_hitboxHeight = 105.f;
    this->_hitboxWidth = 0.f;
    this->_shield = sf::RectangleShape(sf::Vector2f(50, 50));
    this->_shield.setTexture(&this->_shieldTexture);
    this->_pathWinTexture = "assets/player/SmallWin/ezgif-frame-";
    this->_soundBufferAttack.loadFromFile("assets/sound/smallAttack.ogg");
    this->_soundAttack.setBuffer(this->_soundBufferAttack);
    this->_soundAttack.setVolume(50);
    this->_soundBufferSpecial.loadFromFile("assets/sound/smallSpecial.ogg");
    this->_soundSpecial.setBuffer(this->_soundBufferSpecial);
    this->_soundSpecial.setVolume(50);
}

void Player::initThinPigeon()
{
    initTexture("assets/player/thinPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 3, 3, 4, 4};
    this->_canDoDJump = true;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(69.f, 149.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 149.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setFillColor(sf::Color::Transparent);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(2);
    this->_hitboxHeight = 149.f;
    this->_hitboxWidth = 0.f;
    this->_shield = sf::RectangleShape(sf::Vector2f(60, 60));
    this->_shield.setTexture(&this->_shieldTexture);
    this->_pathWinTexture = "assets/player/ThinWin/ezgif-frame-";
    this->_soundBufferAttack.loadFromFile("assets/sound/thinAttack.ogg");
    this->_soundAttack.setBuffer(this->_soundBufferAttack);
    this->_soundAttack.setVolume(50);
    this->_soundBufferSpecial.loadFromFile("assets/sound/thinSpecial.ogg");
    this->_soundSpecial.setBuffer(this->_soundBufferSpecial);
    this->_soundSpecial.setVolume(50);
}

void Player::initMuscularPigeon()
{
    initTexture("assets/player/muscularPigeon.png");
    std::vector<int> _array = {1, 1, 8, 8, 5, 5, 5, 5};
    this->_canDoDJump = false;
    initSprite(_array);

    this->_playerColision = sf::RectangleShape(sf::Vector2f(80.f, 130.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 130.f;
    pos.x += 20.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setFillColor(sf::Color::Transparent);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(2);
    this->_hitboxHeight = 130.f;
    this->_hitboxWidth = 20.f;
    this->_shield = sf::RectangleShape(sf::Vector2f(80, 80));
    this->_shield.setTexture(&this->_shieldTexture);
    this->_pathWinTexture = "assets/player/MuscularWin/ezgif-frame-";
    this->_soundBufferAttack.loadFromFile("assets/sound/muscularAttack.ogg");
    this->_soundAttack.setBuffer(this->_soundBufferAttack);
    this->_soundAttack.setVolume(50);
    this->_soundBufferSpecial.loadFromFile("assets/sound/muscularSpecial.ogg");
    this->_soundSpecial.setBuffer(this->_soundBufferSpecial);
    this->_soundSpecial.setVolume(50);
}
