#include "Unit.h"

Unit::Unit(int id, Point location, Owner owner, UnitType type, int health, int level, Path* path)
        : Entity(id, location, owner)
        , m_type(type)
        , m_health(health)
        , m_level(level)
        , m_path(path)
{
}

void Unit::set_type(UnitType type) {
    m_type = type;
}

UnitType Unit::get_type() const {
    return m_type;
}

void Unit::set_health(int health) {
    m_health = health;
}

int Unit::get_health() const {
    return m_health;
}

void Unit::set_level(int level) {
    m_level = level;
}

int Unit::get_level() const {
    return m_level;
}

void Unit::set_path(Path* path) {
    m_path = path;
}

Path* Unit::get_path() const {
    return m_path;
}

template <UnitType type>
UnitImpl<type>::UnitImpl(int id, Point location, Owner owner, int health, int level, Path* path)
        : Unit(id, location, owner, type, health, level, path)
{
}

template <UnitType type>
int UnitImpl<type>::get_price() const {
    return INITIAL_PRICE + (get_level() - 1 ) * PRICE_INCREASE;
}

template <UnitType type>
int UnitImpl<type>::get_added_income() const {
    return ADDED_INCOME;
}

template <UnitType type>
int UnitImpl<type>::get_bounty() const {
    return INITIAL_BOUNTY + ( get_level() -1 )* BOUNTY_INCREASE;
}

template <UnitType type>
int UnitImpl<type>::get_damage() const {
    return DAMAGE;
}

template <UnitType type>
int UnitImpl<type>::get_move_speed() const {
    return MOVE_SPEED;
}

template <UnitType type>
int UnitImpl<type>::get_vision_range() const {
    return VISION_RANGE;
}

template <UnitType type>
UnitImpl<type>* UnitImpl<type>::clone() {
    return new UnitImpl<type>(*this);
}

template <UnitType type>
int UnitImpl<type>::INITIAL_PRICE = 0;

template <UnitType type>
int UnitImpl<type>::PRICE_INCREASE = 0;

template <UnitType type>
int UnitImpl<type>::INITIAL_HEALTH = 0;

template <UnitType type>
double UnitImpl<type>::HEALTH_COEFF = 0.0;

template <UnitType type>
int UnitImpl<type>::INITIAL_BOUNTY = 0;

template <UnitType type>
int UnitImpl<type>::BOUNTY_INCREASE = 0;

template <UnitType type>
int UnitImpl<type>::MOVE_SPEED = 0;

template <UnitType type>
int UnitImpl<type>::DAMAGE = 0;

template <UnitType type>
int UnitImpl<type>::VISION_RANGE = 0;

template <UnitType type>
int UnitImpl<type>::ADDED_INCOME = 0;

template <UnitType type>
int UnitImpl<type>::LEVEL_UP_THRESHOLD = 0;

template class UnitImpl<UnitType::HEAVY>;
template class UnitImpl<UnitType::LIGHT>;

