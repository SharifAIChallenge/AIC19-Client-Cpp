#ifndef AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H

#include "Message.h"
#include "../../Model/Tower.h"

class CreateTowerMessage final : public Message {
public:

    inline CreateTowerMessage(TowerType type, int level, Point location)
            : Message()
    {
        m_root["type"] = "ct";
        m_root["args"].append(type == TowerType::CANNON ? "c" : "a");
        m_root["args"].append(level);
        m_root["args"].append(location.get_x());
        m_root["args"].append(location.get_y());
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_TOWER_MESSAGE_H
