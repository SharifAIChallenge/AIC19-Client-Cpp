#ifndef AIC18_CLIENT_CPP_TOWER_H
#define AIC18_CLIENT_CPP_TOWER_H

#include "Entity.h"

/**
 * A defending tower
 */
class Tower : public Entity {
public:

    Tower() = default;
    ~Tower() override = default;

    Tower(const Tower&) = default;
    Tower& operator= (const Tower&) = default;

    Tower(int id, Point location, Owner owner, int level, int price, int damage, int attack_speed, int attack_range);

    void set_level(int level);
    int get_level() const;

    void set_price(int price);
    int get_price() const;

    void set_damage(int damage);
    int get_damage() const;

    void set_attack_speed(int attack_speed);
    int get_attack_speed() const;

    void set_attack_range(int attack_range);
    int get_attack_range() const;

private:

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

class CannonTower : public Tower {
public:

    CannonTower() = default;
    ~CannonTower() override = default;

    CannonTower(const CannonTower&) = default;
    CannonTower& operator=(const CannonTower&) = default;

    CannonTower(int id, Point location, Owner owner, int level, int price, int damage, int attack_speed,
                int attack_range);

    static int INITIAL_PRICE;
    static int INITIAL_LEVEL_UP_PRICE;
    static double PRICE_COEFF;

    static int INITIAL_DAMAGE;
    static double DAMAGE_COEFF;

    static int ATTACK_RANGE;
};

class ArcherTower : public Tower {
public:

    ArcherTower() = default;
    ~ArcherTower() override = default;

    ArcherTower(const ArcherTower&) = default;
    ArcherTower& operator=(const ArcherTower&) = default;

    ArcherTower(int id, Point location, Owner owner, int level, int price, int damage, int attack_speed,
                int attack_range);

    static int INITIAL_PRICE;
    static int INITIAL_LEVEL_UP_PRICE;
    static double PRICE_COEFF;

    static int INITIAL_DAMAGE;
    static double DAMAGE_COEFF;

    static int ATTACK_RANGE;
};

#endif // AIC18_CLIENT_CPP_TOWER_H
