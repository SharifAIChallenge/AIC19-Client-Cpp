#ifndef AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H

#include "Message.h"
#include "../../Model/Unit.h"

class CreateUnitMessage final : public Message {
public:

    inline CreateUnitMessage(UnitType type, int path_index)
            : Message()
    {
        m_root["type"] = "cu";
        m_root["args"].append(type == UnitType::LIGHT ? "h" : "l");
        m_root["args"].append(path_index);
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
