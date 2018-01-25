#ifndef AIC18_CLIENT_CPP_UNIT_H
#define AIC18_CLIENT_CPP_UNIT_H

#include "Entity.h"
#include "Path.h"

/**
 * Type of a unit
 */
enum class UnitType {
    HEAVY,
    LIGHT
};

/**
 * An attacking unit in the game
 */
class Unit : public Entity {
public:

    Unit() = default;
    ~Unit() override = default;

    Unit(const Unit&) = default;
    Unit& operator= (const Unit&) = default;

    Unit(UnitType type, int health, int level, int price, int added_income, int bounty, int damage, int move_speed,
        int vision_range, const Path& path);

    void set_type(UnitType type);
    void set_health(int health);
    void set_level(int level);
    void set_price(int price);
    void set_added_income(int added_income);
    void set_bounty(int bounty);
    void set_damage(int damage);
    void set_move_speed(int move_speed);
    void set_vision_range(int vision_range);
    void set_path(const Path& path);

    UnitType get_type() const;
    int get_health() const;
    int get_level() const;
    int get_price() const;
    int get_added_income() const;
    int get_bounty() const;
    int get_damage() const;
    int get_move_speed() const;
    int get_vision_range() const;
    const Path& get_path() const;

private:

    /// The type of this unit
    UnitType m_type;

    /// Current amount of health
    int m_health;

    /// Current level
    int m_level;

    /// Price to build this unit
    int m_price;

    /// Amount of income added to player's income after creating this unit
    int m_added_income;

    /// The money rewarded to the enemy if this unit is killed
    int m_bounty;

    /// Amount of damage this unit does to enemy's health if it passes the path
    int m_damage;

    /// Number of time cycles this unit needs to pass a single cell on map
    int m_move_speed;

    /// Maximum distance of map cells this unit sees
    int m_vision_range;

    /// Pointer to the path this unit is on
    const Path* m_path;
};

#endif // AIC18_CLIENT_CPP_UNIT_H
