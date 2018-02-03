#ifndef AIC18_CLIENT_CPP_UNIT_H
#define AIC18_CLIENT_CPP_UNIT_H

#include <memory>

#include "Entity.h"
#include "Path.h"

enum UnitType {
    HEAVY = 0,
    LIGHT = 1
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

    Unit(int id, Point location, Owner owner, UnitType type,
         int health, int level, int price, int added_income, int bounty, int damage,int move_speed, int vision_range,
         const std::shared_ptr<const Path>& path);

    void set_type(UnitType type);
    UnitType get_type() const;

    void set_health(int health);
    int get_health() const;

    void set_level(int level);
    int get_level() const;

    void set_price(int price);
    int get_price() const;

    void set_added_income(int added_income);
    int get_added_income() const;

    void set_bounty(int bounty);
    int get_bounty() const;

    void set_damage(int damage);
    int get_damage() const;

    void set_move_speed(int move_speed);
    int get_move_speed() const;

    void set_vision_range(int vision_range);
    int get_vision_range() const;

    void set_path(const std::shared_ptr<const Path>& path);
    const Path* get_path() const;

private:

    /// Type of this unit
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
    std::shared_ptr<const Path> m_path;
};

class HeavyUnit : public Unit {
public:

    HeavyUnit() = default;
    ~HeavyUnit() override = default;

    HeavyUnit(const HeavyUnit&) = default;
    HeavyUnit& operator= (const HeavyUnit&) = default;

    HeavyUnit(int id, Point location, Owner owner,
         int health, int level, int price, int added_income, int bounty, int damage,int move_speed, int vision_range,
         const std::shared_ptr<const Path>& path);

    static int INITIAL_PRICE;
    static int PRICE_INCREASE;

    static int INITIAL_HEALTH;
    static double HEALTH_COEFF;

    static int INITIAL_BOUNTY;
    static int BOUNTY_INCREASE;

    static int MOVE_SPEED;
    static int DAMAGE;
    static int VISION_RANGE;

    static int LEVEL_UP_THRESHOLD;
};

class LightUnit : public Unit {
public:
    LightUnit() = default;
    ~LightUnit() override = default;

    LightUnit(const LightUnit&) = default;
    LightUnit& operator= (const LightUnit&) = default;

    LightUnit(int id, Point location, Owner owner,
         int health, int level, int price, int added_income, int bounty, int damage,int move_speed, int vision_range,
         const std::shared_ptr<const Path>& path);

    static int INITIAL_PRICE;
    static int PRICE_INCREASE;

    static int INITIAL_HEALTH;
    static double HEALTH_COEFF;

    static int INITIAL_BOUNTY;
    static int BOUNTY_INCREASE;

    static int MOVE_SPEED;
    static int DAMAGE;
    static int VISION_RANGE;

    static int LEVEL_UP_THRESHOLD;
};

#endif // AIC18_CLIENT_CPP_UNIT_H
