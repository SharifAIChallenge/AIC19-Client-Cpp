#include "Tower.h"

Tower::Tower(TowerType type, int level, int price, int damage, int attack_speed, int attack_range)
        : m_type(type)
        , m_level(level)
        , m_price(price)
        , m_damage(damage)
        , m_attack_speed(attack_speed)
        , m_attack_range(attack_range)
{
}

void Tower::set_type(TowerType type) {
    m_type = type;
}

void Tower::set_level(int level) {
    m_level = level;
}

void Tower::set_price(int price) {
    m_price = price;
}

void Tower::set_damage(int damage) {
    m_damage = damage;
}

void Tower::set_attack_speed(int attack_speed) {
    m_attack_speed = attack_speed;
}

void Tower::set_attack_range(int attack_range) {
    m_attack_range = attack_range;
}

TowerType Tower::get_type() const {
    return m_type;
}

int Tower::get_level() const {
    return m_level;
}

int Tower::get_price() const {
    return m_price;
}

int Tower::get_damage() const {
    return m_damage;
}

int Tower::get_attack_speed() const {
    return m_attack_speed;
}

int Tower::get_attack_range() const {
    return m_attack_range;
}

int CannonTower::INITIAL_PRICE = 0;
int CannonTower::INITIAL_LEVEL_UP_PRICE = 0;
int CannonTower::PRICE_COEFF = 0;
int CannonTower::INITIAL_DAMAGE = 0;
int CannonTower::DAMAGE_COEFF = 0;
int CannonTower::INITIAL_ATTACK_RANGE = 0;
int CannonTower::ATTACK_RANGE_SUM = 0;

int ArcherTower::INITIAL_PRICE = 0;
int ArcherTower::INITIAL_LEVEL_UP_PRICE = 0;
int ArcherTower::PRICE_COEFF = 0;
int ArcherTower::INITIAL_DAMAGE = 0;
int ArcherTower::DAMAGE_COEFF = 0;
int ArcherTower::INITIAL_ATTACK_RANGE = 0;
int ArcherTower::ATTACK_RANGE_SUM = 0;
