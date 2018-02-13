#ifndef AIC18_CLIENT_CPP_UNIT_H
#define AIC18_CLIENT_CPP_UNIT_H

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
         int health, int level, Path* path);

    virtual Unit* clone() = 0;

    void set_type(UnitType type);
    UnitType get_type() const;

    void set_health(int health);
    int get_health() const;

    void set_level(int level);
    int get_level() const;

    void set_path(Path* path);
    Path* get_path() const;

    virtual int get_price() const = 0;
    virtual int get_added_income() const = 0;
    virtual int get_bounty() const = 0;
    virtual int get_damage() const = 0;
    virtual int get_move_speed() const = 0;
    virtual int get_vision_range() const = 0;

private:

    /// Type of this unit
    UnitType m_type;

    /// Current amount of health
    int m_health;

    /// Current level
    int m_level;

    /// Pointer to the path this unit is on
    Path* m_path;
};

template <UnitType type>
class UnitImpl : public Unit {
public:

    UnitImpl() = default;
    ~UnitImpl() override = default;

    UnitImpl(const UnitImpl&) = default;
    UnitImpl& operator= (const UnitImpl&) = default;

    UnitImpl(int id, Point location, Owner owner, int health, int level, Path* path);

    UnitImpl* clone() override;

    int get_price() const override;
    int get_added_income() const override;
    int get_bounty() const override;
    int get_damage() const override;
    int get_move_speed() const override;
    int get_vision_range() const override;

    static int INITIAL_PRICE;
    static int PRICE_INCREASE;

    static int INITIAL_HEALTH;
    static double HEALTH_COEFF;

    static int INITIAL_BOUNTY;
    static int BOUNTY_INCREASE;

    static int MOVE_SPEED;
    static int DAMAGE;
    static int VISION_RANGE;
    static int ADDED_INCOME;

    static int LEVEL_UP_THRESHOLD;
};

using HeavyUnit = UnitImpl<UnitType::HEAVY>;
using LightUnit = UnitImpl<UnitType::LIGHT>;

#endif // AIC18_CLIENT_CPP_UNIT_H
