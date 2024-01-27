/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Player
*/

#include "./player/Player.hpp"

Player::Player(PlayerType type)
{
    init(type);
}

Player::~Player()
{
}

void Player::handleEvent(sf::Event event, Map *map)
{
    this->_oldPlayerPos = this->_playerPos;
    if (sf::Keyboard::isKeyPressed(this->_right)) {
        this->move({5.f,0.f}, map);
    }
    if (sf::Keyboard::isKeyPressed(this->_left)) {
        this->move({-5.f,0.f}, map);
    }
    if (sf::Keyboard::isKeyPressed(this->_up)) {
        this->jump();
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == this->_up) {
            if (_isJumping == FIRSTJUMP)
                this->_isJumping = CANDJUMP;
        }
    }
    if (sf::Keyboard::isKeyPressed(this->_attack)) {
        updateAttackColision();
        this->isAttacking = true;
    }
    if (sf::Keyboard::isKeyPressed(this->_displayColision)) {
        this->displayColision = !this->displayColision;
    }
}

void Player::jump()
{
    if (this->_isJumping == false) {
        this->_acceleration.y = 0;
        this->_velocity.y = -6.f;
        this->_isFly = true;
        this->_isJumping = FIRSTJUMP;
        return;
    }
     else if (this->_isJumping == CANDJUMP){
        this->_acceleration.y = 0;
        this->_velocity.y = -7.f;
        this->_isFly = true;
        this->_isJumping = DOUBLEJUMP;
        return;
    }
}

void Player::stateFly(bool state)
{
    this->_isFly = state;
}

void Player::resetJump()
{
    this->_isJumping = NOJUMP;
}

void Player::update(Map *map)
{
    this->_acceleration.y += this->_gravity;
    this->_velocity.y += this->_acceleration.y;
    if (this->_velocity.y > 15.f)
        this->_velocity.y = 15.f;
    move({0,this->_velocity.y}, map);
}

void Player::draw(sf::RenderWindow &window)
{
    updateColision();
    window.draw(this->_player);
    if (this->isAttacking) {
        window.draw(this->_playerAttackColision);
        this->isAttacking = false;
    }
    if (this->displayColision)
        displayColisionHitBox(window);
}

void Player::move(sf::Vector2f move, Map *map)
{
    this->_oldPlayerPos = this->_playerPos;
    this->_playerPos += move;
    this->_player.setPosition(this->_playerPos);
    updateColision();
    if (isColliding(map)) {
        stateFly(false);
        resetJump();
        setPlayerPos(this->_oldPlayerPos);
    }
}

void Player::setPlayerPos(sf::Vector2f pos)
{
    this->_playerPos = pos;
    this->_player.setPosition(this->_playerPos);
    updateColision();
}

void Player::displayColisionHitBox(sf::RenderWindow &window)
{
    window.draw(this->_playerColision);
}

void Player::init(PlayerType type)
{
    initTexture();
    initSprite();
    initPos();
    // initOrigin();
    initSpeed();
    this->_oldPlayerPos = this->_playerPos;
    this->lookingRight = true;
    this->isAttacking = false;
    this->displayColision = false;
    this->_isJumping = JumpType::NOJUMP;
    this->_gravity = 0.01f;
    this->_jumpForce = 6.f;
    this->_velocity = {0,0};
    this->_acceleration = {0,0};
    initColision();
    initAttackColision(50);
    if (type == PlayerType::PLAYER1) {
        this->_right = sf::Keyboard::D;
        this->_left = sf::Keyboard::Q;
        this->_up = sf::Keyboard::Z;
        this->_attack = sf::Keyboard::E;
        this->_jump = sf::Keyboard::Space;
        this->_displayColision = sf::Keyboard::A;
    } else {
        this->_right = sf::Keyboard::Right;
        this->_left = sf::Keyboard::Left;
        this->_up = sf::Keyboard::Up;
        this->_attack = sf::Keyboard::Numpad0;
        this->_jump = sf::Keyboard::Numpad1;
        this->_displayColision = sf::Keyboard::Numpad2;
    }
}

void Player::initSprite()
{
    this->_player.setTexture(this->_playerTexture);
}

void Player::initTexture()
{
    this->_playerTexture.loadFromFile("assets/player/player.png");
}

void Player::initPos()
{
    this->_playerPos = sf::Vector2f(0, 0);
    this->_player.setPosition(this->_playerPos);
}

void Player::initSpeed()
{
    this->_playerSpeed = sf::Vector2f(0, 0);
}

void Player::initColision()
{
    this->_playerColision = sf::RectangleShape(sf::Vector2f(69.f, 173.f));
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - 173.f;
    this->_playerColision.setPosition(pos);
    this->_playerColision.setOutlineColor(sf::Color::Green);
    this->_playerColision.setOutlineThickness(3);
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

void Player::updateAttackColision()
{
    if (this->lookingRight) {
        this->_playerAttackColision.setPosition(this->_playerPos.x + this->_playerColision.getGlobalBounds().width, this->_playerPos.y);
    } else {
        this->_playerAttackColision.setPosition(this->_playerPos.x - this->reachSize, this->_playerPos.y);
    }
}

bool Player::isColliding(Map *map)
{
    std::vector<sf::RectangleShape> colision = map->getColision();

    for (size_t i = 0; i < map->getNbCollisionShape(); i++) {
        if (this->_playerColision.getGlobalBounds().intersects(colision[i].getGlobalBounds()))
            return true;
    }
    return false;
}

void Player::clean()
{
}
