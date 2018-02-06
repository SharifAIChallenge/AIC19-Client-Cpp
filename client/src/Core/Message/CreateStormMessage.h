#ifndef AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H

#include <Model/Point.h>
#include "Message.h"

class CreateStormMessage final : public Message {
public:

    inline explicit CreateStormMessage(Point location)
            : Message()
    {
        m_root["name"] = "event";
        Json::Value& args = m_root["args"][0];

        args["type"] = "s";
        args["args"].append(location.get_x());
        args["args"].append(location.get_y());
    }
};

#endif // AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H
