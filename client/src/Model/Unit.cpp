#include "Unit.h"

Unit::Unit(int id, Point location, Owner owner, UnitType type, int health, int level, int price, int added_income,
           int bounty, int damage, int move_speed, int vision_range, const Path* path)
        : Entity(id, location, owner)
        , m_type(type)
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

void Unit::set_price(int price) {
    m_price = price;
}

int Unit::get_price() const {
    return m_price;
}

void Unit::set_added_income(int added_income) {
    m_added_income = added_income;
}

int Unit::get_added_income() const {
    return m_added_income;
}

void Unit::set_bounty(int bounty) {
    m_bounty = bounty;
}

int Unit::get_bounty() const {
    return m_bounty;
}

void Unit::set_damage(int damage) {
    m_damage = damage;
}

int Unit::get_damage() const {
    return m_damage;
}

void Unit::set_move_speed(int move_speed) {
    m_move_speed = move_speed;
}

int Unit::get_move_speed() const {
    return m_move_speed;
}

void Unit::set_vision_range(int vision_range) {
    m_vision_range = vision_range;
}

int Unit::get_vision_range() const {
    return m_vision_range;
}

void Unit::set_path(const Path* path) {
    m_path = path;
}

const Path* Unit::get_path() const {
    return m_path;
}

HeavyUnit::HeavyUnit(int id, Point location, Owner owner, int health, int level, int price, int added_income,
                     int bounty, int damage, int move_speed, int vision_range, const Path* path)
        : Unit(id, location, owner, UnitType::HEAVY, health, level, price, added_income, bounty, damage, move_speed,
               vision_range, path)
{
}

int HeavyUnit::INITIAL_PRICE = 0;
int HeavyUnit::PRICE_INCREASE = 0;
int HeavyUnit::INITIAL_HEALTH = 0;
double HeavyUnit::HEALTH_COEFF = 0.0;
int HeavyUnit::INITIAL_BOUNTY = 0;
int HeavyUnit::BOUNTY_INCREASE = 0;
int HeavyUnit::MOVE_SPEED = 0;
int HeavyUnit::DAMAGE = 0;
int HeavyUnit::VISION_RANGE = 0;
int HeavyUnit::ADDED_INCOME = 0;
int HeavyUnit::LEVEL_UP_THRESHOLD = 0;

LightUnit::LightUnit(int id, Point location, Owner owner, int health, int level, int price, int added_income,
                     int bounty, int damage, int move_speed, int vision_range, const Path* path)
        : Unit(id, location, owner, UnitType::LIGHT, health, level, price, added_income, bounty, damage, move_speed,
               vision_range, path)
{
}

int LightUnit::INITIAL_PRICE = 0;
int LightUnit::PRICE_INCREASE = 0;
int LightUnit::INITIAL_HEALTH = 0;
double LightUnit::HEALTH_COEFF = 0.0;
int LightUnit::INITIAL_BOUNTY = 0;
int LightUnit::BOUNTY_INCREASE = 0;
int LightUnit::MOVE_SPEED = 0;
int LightUnit::DAMAGE = 0;
int LightUnit::VISION_RANGE = 0;
int LightUnit::ADDED_INCOME = 0;
int LightUnit::LEVEL_UP_THRESHOLD = 0;
