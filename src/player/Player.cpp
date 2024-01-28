/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Player
*/

#include "./player/Player.hpp"


Player::Player(PlayerType playerType, PigeonType pigeonType, sf::Vector2f pos)
{
    init(playerType, pigeonType, pos);
}

Player::~Player()
{
}

void Player::handleEvent(sf::Event event, Map *map)
{
    this->_map = map;
    if(this->_type == PigeonType::THIN_PIGEON && (this->_anim == SPECIALR || this->_anim == SPECIALL)){
        if (sf::Keyboard::isKeyPressed(this->_right))
            this->move({5.f,0.f}, map);
        if (sf::Keyboard::isKeyPressed(this->_left))
            this->move({-5.f,0.f}, map);
        return;
    }
    if ((this->_respawnClock.getElapsedTime().asSeconds() < RESPAWN_DELAY  || this->_attackClock.getElapsedTime().asSeconds() < 0.4f || this->_SpecialClock.getElapsedTime().asSeconds() < 0.4f)){
        this->_velocity = {0,0};
        this->_acceleration = {0,0};
        return;
    }
    this->_oldPlayerPos = this->_playerPos;
    if (sf::Keyboard::isKeyPressed(this->_right)) {
        this->lookingRight = true;
        this->move({5.f,0.f}, map);
        this->_anim = WALKR;
    }
    if (sf::Keyboard::isKeyPressed(this->_left)) {
        this->lookingRight = false;
        this->move({-5.f,0.f}, map);
        this->_anim = WALKL;
    }
    if (sf::Keyboard::isKeyPressed(this->_up)) {
        this->jump();
    }
    if (event.type == sf::Event::KeyReleased) {
        if (event.key.code == this->_left)
            this->_anim = IDLEL;
        if (event.key.code == this->_right)
            this->_anim = IDLER;
        if (event.key.code == this->_up) {
            if (_isJumping == FIRSTJUMP)
                this->_isJumping = CANDJUMP;
        }
    }
    if (sf::Keyboard::isKeyPressed(this->_displayColision)) {
        this->displayColision = !this->displayColision;
    }
}

void Player::jump()
{
    if (this->_isJumping == false) {
        this->_acceleration.y = 0;
        this->_velocity.y = this->_jumpForce;
        this->_isFly = true;
        this->_isJumping = FIRSTJUMP;
        return;
    }
     else if (this->_isJumping == CANDJUMP && this->_canDoDJump == true){
        this->_acceleration.y = 0;
        this->isSpecial = true;
        this->_attackClock.restart();
        this->_velocity.y = this->_jumpForce;
        this->_isFly = true;
        this->_isJumping = DOUBLEJUMP;
        return;
    }
}

void Player::resetJump()
{
    this->_isJumping = NOJUMP;
}

void Player::update(Map *map)
{
    updateTextureRect();
    updateColision();
    updateAttackAnimation();
    updateSpecialAnimation();
    attackResetAnim();
    makeDash();
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
    if (this->displayColision)
        displayColisionHitBox(window);
    if (this->_respawnClock.getElapsedTime().asSeconds() < RESPAWN_DELAY) {
        sf::RectangleShape respawn(sf::Vector2f(100, 100));
        respawn.setPosition(this->_playerPos);
        respawn.setFillColor(sf::Color::Red);
        window.draw(respawn);
    }
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

void Player::respawn(sf::Vector2f spawnPos)
{
    this->_playerPos = spawnPos;
    this->_player.setPosition(this->_playerPos);
    this->_nbLife--;
    this->_respawnClock.restart();
    updateColision();
}

sf::Keyboard::Key Player::getAttackKey() const
{
    return this->_attack;
}

sf::Keyboard::Key Player::getSpecial() const
{
    return this->_special;
}

sf::Vector2f Player::getPos() const
{
    return this->_playerPos;
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

sf::FloatRect Player::getBound()
{
    return this->_playerColision.getGlobalBounds();
}
