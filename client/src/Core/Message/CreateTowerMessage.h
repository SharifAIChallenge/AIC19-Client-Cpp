#ifndef AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H

#include <Model/Tower.h>
#include "Message.h"

class CreateTowerMessage final : public Message {
public:

    inline CreateTowerMessage(TowerType type, int level, Point location)
            : Message()
    {
        m_root["name"] = "event";
        Json::Value& args = m_root["args"][0];

        args["type"] = "ct";
        args["args"].append(type == TowerType::CANNON ? "c" : "a");
        args["args"].append(level);
        args["args"].append(location.get_x());
        args["args"].append(location.get_y());
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H
