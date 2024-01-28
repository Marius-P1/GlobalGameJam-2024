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

int Player::useSpecial(Player *player)
{
    if (this->_SpecialClock.getElapsedTime().asSeconds() > SPECIAL_DELAY){
        this->_SpecialClock.restart();
        this->isSpecial = true;
        updateAttackColision();
        if (this->_playerAttackColision.getGlobalBounds().intersects(player->_playerColision.getGlobalBounds())) {
            if (player->_damageClock.getElapsedTime().asSeconds() > DAMAGE_DELAY) {
                player->_damageClock.restart();
                player->_nbLife -= 2;
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
