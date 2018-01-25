#ifndef AIC18_CLIENT_CPP_TOWER_H
#define AIC18_CLIENT_CPP_TOWER_H

#include "Entity.h"

/**
 * Type of a tower
 */
enum class TowerType {
    CANNON,
    ARCHER
};

/**
 * A defending tower
 */
class Tower : public Entity {
public:

    Tower() = default;
    ~Tower() override = default;

    Tower(const Tower&) = default;
    Tower& operator= (const Tower&) = default;

    Tower(TowerType type, int level, int price, int damage, int attack_speed, int attack_range);

    void set_type(TowerType type);
    void set_level(int level);
    void set_price(int price);
    void set_damage(int damage);
    void set_attack_speed(int attack_speed);
    void set_attack_range(int attack_range);

    TowerType get_type() const;
    int get_level() const;
    int get_price() const;
    int get_damage() const;
    int get_attack_speed() const;
    int get_attack_range() const;

private:

    /// The type of this tower
    TowerType m_type;

    /// Current level
    int m_level;

    /// Price paid for building this tower
    int m_price;

    /// The amount of damage this tower does
    int m_damage;

    /// Number of time cycles this tower needs between its shots
    int m_attack_speed;

    /// Maximum distance of the map cells this tower can attack
    int m_attack_range;

};

class CannonTower {
public:

    static int INITIAL_PRICE;
    static int INITIAL_LEVEL_UP_PRICE;
    static int PRICE_COEFF;

    static int INITIAL_DAMAGE;
    static int DAMAGE_COEFF;

    static int INITIAL_ATTACK_RANGE;
    static int ATTACK_RANGE_SUM;
};

class ArcherTower {

    static int INITIAL_PRICE;
    static int INITIAL_LEVEL_UP_PRICE;
    static int PRICE_COEFF;

    static int INITIAL_DAMAGE;
    static int DAMAGE_COEFF;

    static int INITIAL_ATTACK_RANGE;
    static int ATTACK_RANGE_SUM;
};

#endif // AIC18_CLIENT_CPP_TOWER_H
