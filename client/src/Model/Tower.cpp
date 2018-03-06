#include "Tower.h"

#include <cmath>

Tower::Tower(int id, Point location, Owner owner, TowerType type, int level, int price)
        : Entity(id, location, owner)
        , m_type(type)
        , m_level(level)
        , m_price(price)
{
}

void Tower::set_type(TowerType type) {
    m_type = type;
}

TowerType Tower::get_type() const {
    return m_type;
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

template <TowerType type>
TowerImpl<type>::TowerImpl(int id, Point location, Owner owner, int level, int price)
        : Tower(id, location, owner, type, level, price)
{
}

template <TowerType type>
TowerImpl<type>* TowerImpl<type>::clone() {
    return new TowerImpl<type>(*this);
}

template <TowerType type>
int TowerImpl<type>::get_damage() const {
    return static_cast<int>(INITIAL_DAMAGE * std::pow(DAMAGE_COEFF, get_level() - 1));
}

template <TowerType type>
int TowerImpl<type>::get_attack_speed() const {
    return ATTACK_SPEED;
}

template <TowerType type>
int TowerImpl<type>::get_attack_range() const {
    return ATTACK_RANGE;
}

template <TowerType type>
int TowerImpl<type>::INITIAL_PRICE = 0;

template <TowerType type>
int TowerImpl<type>::INITIAL_LEVEL_UP_PRICE = 0;

template <TowerType type>
double TowerImpl<type>::PRICE_COEFF = 0.0;

template <TowerType type>
int TowerImpl<type>::INITIAL_PRICE_INCREASE = 0;

template <TowerType type>
int TowerImpl<type>::INITIAL_DAMAGE = 0;

template <TowerType type>
double TowerImpl<type>::DAMAGE_COEFF = 0.0;

template <TowerType type>
int TowerImpl<type>::ATTACK_SPEED = 0;

template <TowerType type>
int TowerImpl<type>::ATTACK_RANGE = 0;

template class TowerImpl<TowerType::CANNON>;
template class TowerImpl<TowerType::ARCHER>;
