#ifndef AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H

#include <Model/Tower.h>
#include "EventMessage.h"

class CreateTowerMessage final : public EventMessage {
public:

    inline CreateTowerMessage(TowerType type, int level, Point location)
            : EventMessage("ct", {type == TowerType::CANNON ? "c" : "a",
                                  level,
                                  location.x(),
                                  location.y()})
    {
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H
