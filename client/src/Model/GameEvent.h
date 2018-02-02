#ifndef AIC18_CLIENT_CPP_GAME_EVENT_H
#define AIC18_CLIENT_CPP_GAME_EVENT_H

#include "Player.h"
#include "Point.h"

/**
 * An event happened in one turn
 */
class GameEvent {
public:

    GameEvent() = default;
    virtual ~GameEvent() = default;

    GameEvent(const GameEvent&) = default;
    GameEvent& operator= (const GameEvent&) = default;

    GameEvent(Owner owner, Point location);

    void set_owner(Owner owner);
    void set_location(Point location);

    Owner get_owner() const;
    Point get_location() const;

private:

    /// Who caused the event
    Owner m_owner;

    /// Location for this event
    Point m_location;
};

class StormEvent : public GameEvent {
public:

    StormEvent() = default;
    ~StormEvent() override = default;

    StormEvent(const StormEvent&) = default;
    StormEvent& operator= (const StormEvent&) = default;

    StormEvent(Owner owner, Point location);
};

class BeanEvent : public GameEvent {
public:

    BeanEvent() = default;
    ~BeanEvent() override = default;

    BeanEvent(const BeanEvent&) = default;
    BeanEvent& operator= (const BeanEvent&) = default;

    BeanEvent(Owner owner, Point location);
};

#endif // AIC18_CLIENT_CPP_GAME_EVENT_H
