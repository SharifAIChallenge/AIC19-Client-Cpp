#ifndef AIC18_CLIENT_CPP_ENTITY_H
#define AIC18_CLIENT_CPP_ENTITY_H

#include "Point.h"

/**
 * Owner of an entity in the game world
 */
enum class Owner {
    ME,
    ENEMY
};

/**
 * An entity in the game world
 */
class Entity {
public:

    Entity() = default;
    virtual ~Entity() = default;

    Entity(const Entity&) = default;
    Entity& operator= (const Entity&) = default;

    Entity(Point location, Owner owner);

    void set_location(Point location);
    void set_owner(Owner owner);

    Point get_location() const;
    Owner get_owner() const;

private:

    /// The location of this entity on the game map
    Point m_location;

    /// Owner of this entity
    Owner m_owner;
};

#endif //AIC18_CLIENT_CPP_ENTITY_H
