/*
** EPITECH PROJECT, 2024
** GlobalGameJam-2024
** File description:
** Player
*/

#include "./player/Player.hpp"

static const float RESPAWN_DELAY = 0.5f;
static const float DAMAGE_DELAY = 2.f;
static const float ATTACK_DELAY = 1.f;
static const int ATTACK_RANGE = 80;

Player::Player(PlayerType playerType, PigeonType pigeonType, sf::Vector2f pos)
{
    init(playerType, pigeonType, pos);
}

Player::~Player()
{
}

void Player::handleEvent(sf::Event event, Map *map)
{
    if (this->_respawnClock.getElapsedTime().asSeconds() < RESPAWN_DELAY  || this->_attackClock.getElapsedTime().asSeconds() < 0.4f){
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
        this->_velocity.y = this->_jumpForce;
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
    updateTextureRect();
    updateColision();
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
    updateAttackAnimation();
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

void Player::updateAttackAnimation()
{
    if (this->isAttacking) {
        this->_timeAttack = this->_attackClock.getElapsedTime().asSeconds();
        if (this->lookingRight)
            this->_anim = ATTACKR;
        else
            this->_anim = ATTACKL;
        this->isAttacking = false;
    }
    if (this->_attackClock.getElapsedTime().asSeconds() - this->_timeAttack > 0.5f){
        if (this->lookingRight)
                this->_anim = IDLER;
            else
                this->_anim = IDLEL;
    }
}

int Player::useAttack(Player *player)
{
    if (this->_attackClock.getElapsedTime().asSeconds() > ATTACK_DELAY) {
        this->_attackClock.restart();
        this->isAttacking = true;
        updateAttackColision();
        if (this->_playerAttackColision.getGlobalBounds().intersects(player->_playerColision.getGlobalBounds())) {
            if (player->_damageClock.getElapsedTime().asSeconds() > DAMAGE_DELAY) {
                player->_damageClock.restart();
                player->_nbLife--;
            }
        }
    }
    return player->_nbLife;
}

sf::Keyboard::Key Player::getAttackKey() const
{
    return this->_attack;
}

sf::Vector2f Player::getPos() const
{
    return this->_playerPos;
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

void Player::init(PlayerType numberOfThePlayer, PigeonType pigeonType, sf::Vector2f spawnPos)
{
    initPos(spawnPos);
    initVariables();

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
        this->_jump = sf::Keyboard::Space;
        this->_displayColision = sf::Keyboard::K;
    } else {
        this->_right = sf::Keyboard::Right;
        this->_left = sf::Keyboard::Left;
        this->_up = sf::Keyboard::Up;
        this->_attack = sf::Keyboard::Numpad0;
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

void Player::initVariables()
{
    this->_oldPlayerPos = this->_playerPos;
    this->lookingRight = true;
    this->isAttacking = false;
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
