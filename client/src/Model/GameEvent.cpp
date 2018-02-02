#include "GameEvent.h"

GameEvent::GameEvent(Owner owner, Point location)
        : m_owner(owner)
        , m_location(location)
{
}

void GameEvent::set_owner(Owner owner) {
    m_owner = owner;
}

void GameEvent::set_location(Point location) {
    m_location = location;
}

Owner GameEvent::get_owner() const {
    return m_owner;
}

Point GameEvent::get_location() const {
    return m_location;
}

StormEvent::StormEvent(Owner owner, Point location)
        : GameEvent(owner, location)
{
}

BeanEvent::BeanEvent(Owner owner, Point location)
        : GameEvent(owner, location)
{
}
