#ifndef AIC18_CLIENT_CPP_TOWER_H
#define AIC18_CLIENT_CPP_TOWER_H

#include "Entity.h"

enum TowerType {
    CANNON = 0,
    ARCHER = 1
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

    Tower(int id, Point location, Owner owner, TowerType type, int level, int price);

    virtual Tower* clone() = 0;

    void set_type(TowerType type);
    TowerType get_type() const;

    void set_level(int level);
    int get_level() const;

    void set_price(int price);
    int get_price() const;

    virtual int get_damage() const = 0;
    virtual int get_attack_speed() const = 0;
    virtual int get_attack_range() const = 0;

private:

    /// Type of this tower
    TowerType m_type;

    /// Current level
    int m_level;

    /// Price paid to create this tower (excluding upgrades)
    int m_price;
};

template <TowerType type>
class TowerImpl : public Tower {
public:

    TowerImpl() = default;
    ~TowerImpl() override = default;

    TowerImpl(const TowerImpl&) = default;
    TowerImpl& operator=(const TowerImpl&) = default;

    TowerImpl(int id, Point location, Owner owner, int level, int price);

    TowerImpl* clone() override;

    int get_damage() const override;
    int get_attack_speed() const override;
    int get_attack_range() const override;

    static int INITIAL_PRICE;
    static int INITIAL_LEVEL_UP_PRICE;
    static double PRICE_COEFF;
    static int INITIAL_PRICE_INCREASE;

    static int INITIAL_DAMAGE;
    static double DAMAGE_COEFF;

    static int ATTACK_SPEED;
    static int ATTACK_RANGE;
};

using CannonTower = TowerImpl<TowerType::CANNON>;
using ArcherTower = TowerImpl<TowerType::ARCHER>;

#endif // AIC18_CLIENT_CPP_TOWER_H
