#ifndef AIC18_CLIENT_CPP_GAME_EVENT_H
#define AIC18_CLIENT_CPP_GAME_EVENT_H

#include "Point.h"
#include "Entity.h"

/**
 * Type of an event
 */
enum class EventType {
    BEAN_EVENT,
    STORM_EVENT
};

/**
 * An event happened in one cycle
 */
class GameEvent {
public:

    GameEvent() = default;
    ~GameEvent() = default;

    GameEvent(const GameEvent&) = default;
    GameEvent& operator= (const GameEvent&) = default;

    GameEvent(EventType type, Owner owner, Point location);

    void set_type(EventType type);
    void set_owner(Owner owner);
    void set_location(Point location);

    EventType get_type() const;
    Owner get_owner() const;
    Point get_location() const;

private:

    /// Bean or storm?
    EventType m_type;

    /// Who caused the event
    Owner m_owner;

    /// Location for this event
    Point m_location;
};

#endif // AIC18_CLIENT_CPP_GAME_EVENT_H
