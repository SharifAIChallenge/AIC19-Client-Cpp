#include "Player.h"

#include <Utility/Utility.h>

Player::Player(int strength, int money, int income, int beans_left, int storms_left)
        : m_strength(strength)
        , m_money(money)
        , m_income(income)
        , m_beans_left(beans_left)
        , m_storms_left(storms_left)
{
}

void Player::set_strength(int strength) {
    m_strength = strength;
}

int Player::get_strength() const {
    return m_strength;
}

void Player::set_money(int money) {
    m_money = money;
}

int Player::get_money() const {
    return m_money;
}

void Player::set_income(int income) {
    m_income = income;
}

int Player::get_income() const {
    return m_income;
}

void Player::set_beans_left(int beans_left) {
    m_beans_left = beans_left;
}

int Player::get_beans_left() const {
    return m_beans_left;
}

void Player::set_storms_left(int storms_left) {
    m_storms_left = storms_left;
}

int Player::get_storms_left() const {
    return m_storms_left;
}

std::ostream& operator<<(std::ostream &output, const Player& player) {
    return output << format_string("[strength=%d, money=%d, income=%d, beans=%d, storms=%d]",
                                   player.m_strength, player.m_money, player.m_income, player.m_beans_left,
                                   player.m_storms_left);
}
