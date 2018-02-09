#ifndef AIC18_CLIENT_CPP_ENTITY_H
#define AIC18_CLIENT_CPP_ENTITY_H

#include "Point.h"
#include "Player.h"

/**
 * An entity in the game world
 */
class Entity {
public:

    Entity() = default;
    virtual ~Entity() = default;

    Entity(const Entity&) = default;
    Entity& operator= (const Entity&) = default;

    Entity(Entity&&) = default;
    Entity& operator=(Entity&&) = default;

    /**
     * Construct an entity from its parameters
     */
    Entity(int id, Point location, Owner owner);

    void set_id(int id);
    int get_id() const;

    void set_location(Point location);
    Point get_location() const;

    void set_owner(Owner owner);
    Owner get_owner() const;

private:

    /// Unique id for this entity
    int m_id;

    /// The location of this entity on the game map
    Point m_location;

    /// Owner of this entity
    Owner m_owner;
};

#endif //AIC18_CLIENT_CPP_ENTITY_H
