#ifndef AIC18_CLIENT_CPP_END_TURN_MESSAGE_H
#define AIC18_CLIENT_CPP_END_TURN_MESSAGE_H

#include "Message.h"

class EndTurnMessage : public Message {
public:

    inline explicit EndTurnMessage(int turn)
            : Message()
    {
        m_root["name"] = "event";
        Json::Value& args = m_root["args"][0];

        args["type"] = "end";
        args["args"].append(turn);
    }
};

#endif // AIC18_CLIENT_CPP_END_TURN_MESSAGE_H