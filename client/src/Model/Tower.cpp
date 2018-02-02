#include "Tower.h"

Tower::Tower(int id, Point location, Owner owner, int level, int price, int damage, int attack_speed, int attack_range)
        : Entity(id, location, owner)
        , m_level(level)
        , m_price(price)
        , m_damage(damage)
        , m_attack_speed(attack_speed)
        , m_attack_range(attack_range)
{
}

void Tower::set_level(int level) {
    m_level = level;
}

int Tower::get_level() const {
    return m_level;
}

void Tower::set_price(int price) {
    m_price = price;
}

int Tower::get_price() const {
    return m_price;
}

void Tower::set_damage(int damage) {
    m_damage = damage;
}

int Tower::get_damage() const {
    return m_damage;
}

void Tower::set_attack_speed(int attack_speed) {
    m_attack_speed = attack_speed;
}

int Tower::get_attack_speed() const {
    return m_attack_speed;
}

void Tower::set_attack_range(int attack_range) {
    m_attack_range = attack_range;
}

int Tower::get_attack_range() const {
    return m_attack_range;
}

CannonTower::CannonTower(int id, Point location, Owner owner, int level, int price, int damage, int attack_speed,
                         int attack_range)
        : Tower(id, location, owner, level, price, damage, attack_speed, attack_range)
{
}

int CannonTower::INITIAL_PRICE = 0;
int CannonTower::INITIAL_LEVEL_UP_PRICE = 0;
double CannonTower::PRICE_COEFF = 0.0;
int CannonTower::INITIAL_DAMAGE = 0;
double CannonTower::DAMAGE_COEFF = 0.0;
int CannonTower::ATTACK_RANGE = 0;

ArcherTower::ArcherTower(int id, Point location, Owner owner, int level, int price, int damage, int attack_speed,
                         int attack_range)
        : Tower(id, location, owner, level, price, damage, attack_speed, attack_range)
{
}

int ArcherTower::INITIAL_PRICE = 0;
int ArcherTower::INITIAL_LEVEL_UP_PRICE = 0;
double ArcherTower::PRICE_COEFF = 0.0;
int ArcherTower::INITIAL_DAMAGE = 0;
double ArcherTower::DAMAGE_COEFF = 0.0;
int ArcherTower::ATTACK_RANGE = 0;
