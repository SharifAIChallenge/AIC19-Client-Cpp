#ifndef AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H

#include "Message.h"
#include "../../Model/Point.h"

class CreateStormMessage final : public Message {
public:

    inline explicit CreateStormMessage(Point location)
            : Message()
    {
        m_root["type"] = "s";
        m_root["args"].append(location.get_x());
        m_root["args"].append(location.get_y());
    }
};

#endif // AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H
