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

int Entity::get_id() const {
    return m_id;
}

void Entity::set_location(Point location) {
    m_location = location;
}

Point Entity::get_location() const {
    return m_location;
}

void Entity::set_owner(Owner owner) {
    m_owner = owner;
}

Owner Entity::get_owner() const {
    return m_owner;
}
