#ifndef AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H
#define AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H

#include <memory>

#include "Message.h"
#include "../../Model/Tower.h"

class UpgradeTowerMessage final : public Message {
public:

    inline explicit UpgradeTowerMessage(const std::shared_ptr<const Tower>& tower)
            : Message()
    {
        m_root["type"] = "ut";
        m_root["args"].append(tower->get_id());
    }
};

#endif // AIC18_CLIENT_CPP_UPGRADE_TOWER_MESSAGE_H
