#ifndef AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H

#include "Message.h"
#include "../../Model/Unit.h"

class CreateUnitMessage final : public Message {
public:

    inline CreateUnitMessage(UnitType type, const std::shared_ptr<const Path>& path)
            : Message()
    {
        m_root["type"] = "cu";
        m_root["args"].append(type == UnitType::LIGHT ? "h" : "l");
        m_root["args"].append(path->get_id());
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
