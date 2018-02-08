#ifndef AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H
#define AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H

#include <Model/World.h>
#include "EventMessage.h"

class UpgradeTowerMessage final : public EventMessage {
public:

    inline explicit UpgradeTowerMessage(const Tower* tower)
            : EventMessage("ut", {tower->get_id()})
    {
    }
};

#endif // AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H
