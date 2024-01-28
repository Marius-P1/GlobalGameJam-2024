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
static const float SPECIAL_DELAY = 10.f;
static const int ATTACK_RANGE = 80;

Player::Player(PlayerType playerType, PigeonType pigeonType, sf::Vector2f pos)
{
    init(playerType, pigeonType, pos);
}

Player::~Player()
{
    delete this->_spriteSheet;
}

void Player::handleEvent(sf::Event event, Map *map)
{
    this->_map = map;
    if (this->_type == PigeonType::THIN_PIGEON && (this->_anim == SPECIALR || this->_anim == SPECIALL)){
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
    } else if (this->_isJumping == CANDJUMP && this->_canDoDJump == true){
        this->_acceleration.y = 0;
        this->isSpecial = true;
        this->_attackClock.restart();
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

void Player::drawShield(sf::RenderWindow &window)
{
    sf::Vector2f pos = this->_playerColision.getPosition();
    sf::Vector2f size = this->_playerColision.getSize();
    sf::Vector2f shieldSize = this->_shield.getSize();
    sf::Vector2f center = {pos.x + size.x / 2, pos.y + size.y / 2};
    sf::Vector2f shieldPos = {center.x - shieldSize.x / 2, center.y - shieldSize.y / 2};

    this->_shield.setPosition(shieldPos);
    window.draw(this->_shield);
}

void Player::draw(sf::RenderWindow &window)
{
    updateColision();
    window.draw(this->_player);
    if (this->displayColision)
        displayColisionHitBox(window);
    if (this->_respawnClock.getElapsedTime().asSeconds() < RESPAWN_DELAY ||
    this->_damageClock.getElapsedTime().asSeconds() < DAMAGE_DELAY) {
        drawShield(window);
    }
}

void Player::move(sf::Vector2f move, Map *map)
{
    this->_oldPlayerPos = this->_playerPos;
    this->_playerPos += move;
    this->_player.setPosition(this->_playerPos);
    updateColision();
    if (isColliding(map)) {
        if (move.y >= 0) {
            this->_isFly = false;
            resetJump();
        }
        this->_velocity.y = 0;
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

int Player::useAttack(Player *player)
{
    if (this->_attackClock.getElapsedTime().asSeconds() > ATTACK_DELAY) {
        this->_soundAttack.play();
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

int Player::useSpecial(Player *player)
{
    if (this->_SpecialClock.getElapsedTime().asSeconds() > SPECIAL_DELAY){
        this->_SpecialClock.restart();
        this->isSpecial = true;
        this->_canSpecial = true;
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
        this->_playerAttackColision.setPosition(this->_playerPos.x + this->_playerColision.getGlobalBounds().width + this->_hitboxWidth,
        this->_playerPos.y + this->_player.getGlobalBounds().height - this->_hitboxHeight);
    } else {
        this->_playerAttackColision.setPosition(this->_playerPos.x + this->_hitboxWidth - this->reachSize,
        this->_playerPos.y + this->_player.getGlobalBounds().height - this->_hitboxHeight);
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

void Player::updateColision()
{
    sf::Vector2f pos = this->_playerPos;
    pos.y += this->_player.getGlobalBounds().height - this->_hitboxHeight;
    pos.x += this->_hitboxWidth;
    this->_playerColision.setPosition(pos);
    updateAttackColision();
}

sf::FloatRect Player::getBound()
{
    return this->_playerColision.getGlobalBounds();
}

void Player::updateTextureRect()
{
    this->_player.setTextureRect(this->_spriteSheet->animate(this->_anim));
}

int Player::makeDamage(Player *player)
{
    if (this->_canSpecial == true && (this->_anim == SPECIALL || this->_anim == SPECIALR) && this->_playerColision.getGlobalBounds().intersects(player->_playerColision.getGlobalBounds()) ) {
        player->_nbLife -=2;
        this->_canSpecial = false;
    }
    return player->_nbLife;
}

void Player::makeDash()
{
    if (this->_type == PigeonType::FAT_PIGEON || this->_type ==  PigeonType::MUSCULAR_PIGEON || this->_type == PigeonType::SMALL_PIGEON) {
        if (this->_anim == SPECIALR) {
            move({7,0}, this->_map);
        } else if (this->_anim == SPECIALL){
            move({-7,0}, this->_map);
        }
    }
}

void Player::updateAttackAnimation()
{
    if (this->isAttacking) {
        if (this->lookingRight)
            this->_anim = ATTACKR;
        else
            this->_anim = ATTACKL;
        this->isAttacking = false;
    }
}

void Player::attackResetAnim()
{
    if (this->_attackClock.getElapsedTime().asSeconds() > 0.5f &&
    this->_SpecialClock.getElapsedTime().asSeconds() > 0.5f) {
        if (this->lookingRight)
                this->_anim = IDLER;
            else
                this->_anim = IDLEL;
    }
}

void Player::updateSpecialAnimation()
{
    if (this->isSpecial) {
        if (this->lookingRight)
            this->_anim = SPECIALR;
        else
            this->_anim = SPECIALL;
        this->isSpecial = false;
    }
}

sf::Keyboard::Key Player::getSpecial() const
{
    return this->_special;
}

std::string Player::getPathWinTexture() const
{
    return this->_pathWinTexture;
}

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
    this->_playerAttackColision = sf::RectangleShape(sf::Vector2f(this->reachSize, this->_hitboxHeight));
    this->_playerAttackColision.setFillColor(sf::Color::Red);
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
