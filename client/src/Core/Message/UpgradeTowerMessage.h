#ifndef AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H
#define AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H

#include <Model/World.h>
#include "Message.h"

class UpgradeTowerMessage final : public Message {
public:

    inline explicit UpgradeTowerMessage(const Tower* tower)
            : Message()
    {
        m_root["name"] = "event";
        Json::Value& args = m_root["args"][0];

        args["type"] = "ut";
        args["args"].append(tower->get_id());
    }
};

#endif // AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H
