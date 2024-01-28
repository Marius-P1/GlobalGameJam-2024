/*
** EPITECH PROJECT, 2024
** GJ
** File description:
** Attack
*/

#include "./player/Player.hpp"

void Player::stateFly(bool state)
{
    this->_isFly = state;
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


void Player::updateAttackColision()
{
    if (this->lookingRight) {
        this->_playerAttackColision.setPosition(this->_playerPos.x + this->_playerColision.getGlobalBounds().width, this->_playerPos.y);
    } else {
        this->_playerAttackColision.setPosition(this->_playerPos.x - this->reachSize, this->_playerPos.y);
    }
}
