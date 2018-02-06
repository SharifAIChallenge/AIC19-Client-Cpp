#ifndef AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H

#include <Model/Unit.h>
#include "Message.h"

class CreateUnitMessage final : public Message {
public:

    inline CreateUnitMessage(UnitType type, int path_index)
            : Message()
    {
        m_root["name"] = "event";
        Json::Value& args = m_root["args"][0];

        args["type"] = "cu";
        args["args"].append(type == UnitType::LIGHT ? "l" : "h");
        args["args"].append(path_index);
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
