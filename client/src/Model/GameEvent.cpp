#include "GameEvent.h"

GameEvent::GameEvent(EventType type, Owner owner, Point location)
        : m_type(type)
        , m_owner(owner)
        , m_location(location)
{
}

void GameEvent::set_type(EventType type) {
    m_type = type;
}

void GameEvent::set_owner(Owner owner) {
    m_owner = owner;
}

void GameEvent::set_location(Point location) {
    m_location = location;
}

EventType GameEvent::get_type() const {
    return m_type;
}

Owner GameEvent::get_owner() const {
    return m_owner;
}

Point GameEvent::get_location() const {
    return m_location;
}
