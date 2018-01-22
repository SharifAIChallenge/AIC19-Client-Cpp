#include "Player.h"

Player::Player(int health, int money, int income, int beans_left, int storms_left)
        : m_health(health)
        , m_money(money)
        , m_income(income)
        , m_beans_left(beans_left)
        , m_storms_left(storms_left)
{
}

void Player::set_health(int health) {
    m_health = health;
}

void Player::set_money(int money) {
    m_money = money;
}

void Player::set_income(int income) {
    m_income = income;
}

void Player::set_beans_left(int beans_left) {
    m_beans_left = beans_left;
}

void Player::set_storms_left(int storms_left) {
    m_storms_left = storms_left;
}

int Player::get_health() const {
    return m_health;
}

int Player::get_money() const {
    return m_money;
}

int Player::get_income() const {
    return m_income;
}

int Player::get_beans_left() const {
    return m_beans_left;
}

int Player::get_storms_left() const {
    return m_storms_left;
}
