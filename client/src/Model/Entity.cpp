#include "Entity.h"

Entity::Entity(int id, Point location, Owner owner)
        : m_id(id)
        , m_location(location)
        , m_owner(owner)
{
}

void Entity::set_id(int id) {
    m_id = id;
}

void Entity::set_location(Point location) {
    m_location = location;
}

void Entity::set_owner(Owner owner) {
    m_owner = owner;
}

Point Entity::get_location() const {
    return m_location;
}

Owner Entity::get_owner() const {
    return m_owner;
}

int Entity::get_id() const {
    return m_id;
}
