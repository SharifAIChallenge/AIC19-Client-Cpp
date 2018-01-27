#include "Unit.h"

Unit::Unit(UnitType type, int health, int level, int price, int added_income, int bounty, int damage, int move_speed,
           int vision_range, std::shared_ptr<const Path> path)
        : m_type(type)
        , m_health(health)
        , m_level(level)
        , m_price(price)
        , m_added_income(added_income)
        , m_bounty(bounty)
        , m_damage(damage)
        , m_move_speed(move_speed)
        , m_vision_range(vision_range)
        , m_path(path)
{
}

void Unit::set_type(UnitType type) {
    m_type = type;
}

void Unit::set_health(int health) {
    m_health = health;
}

void Unit::set_level(int level) {
    m_level = level;
}

void Unit::set_price(int price) {
    m_price = price;
}

void Unit::set_added_income(int added_income) {
    m_added_income = added_income;
}

void Unit::set_bounty(int bounty) {
    m_bounty = bounty;
}

void Unit::set_damage(int damage) {
    m_damage = damage;
}

void Unit::set_move_speed(int move_speed) {
    m_move_speed = move_speed;
}

void Unit::set_vision_range(int vision_range) {
    m_vision_range = vision_range;
}

void Unit::set_path(std::shared_ptr<const Path> path) {
    m_path = path;
}

UnitType Unit::get_type() const {
    return m_type;
}

int Unit::get_health() const {
    return m_health;
}

int Unit::get_level() const {
    return m_level;
}

int Unit::get_price() const {
    return m_price;
}

int Unit::get_added_income() const {
    return m_added_income;
}

int Unit::get_bounty() const {
    return m_bounty;
}

int Unit::get_damage() const {
    return m_damage;
}

int Unit::get_move_speed() const {
    return m_move_speed;
}

int Unit::get_vision_range() const {
    return m_vision_range;
}

std::shared_ptr<const Path> Unit::get_path() const {
    return m_path;
}

int HeavyUnit::INITIAL_PRICE = 0;
int HeavyUnit::PRICE_SUM = 0;
int HeavyUnit::INITIAL_HEALTH = 0;
int HeavyUnit::HEALTH_COEFF = 0;
int HeavyUnit::INITIAL_BOUNTY = 0;
int HeavyUnit::BOUNTY_SUM = 0;
int HeavyUnit::INITIAL_MOVE_SPEED = 0;
int HeavyUnit::INITIAL_DAMAGE = 0;
int HeavyUnit::INITIAL_VISION_RANGE = 0;

int LightUnit::INITIAL_PRICE = 0;
int LightUnit::PRICE_SUM = 0;
int LightUnit::INITIAL_HEALTH = 0;
int LightUnit::HEALTH_COEFF = 0;
int LightUnit::INITIAL_BOUNTY = 0;
int LightUnit::BOUNTY_SUM = 0;
int LightUnit::INITIAL_MOVE_SPEED = 0;
int LightUnit::INITIAL_DAMAGE = 0;
int LightUnit::INITIAL_VISION_RANGE = 0;
