#ifndef AIC18_CLIENT_CPP_END_TURN_MESSAGE_H
#define AIC18_CLIENT_CPP_END_TURN_MESSAGE_H

#include "EventMessage.h"

class EndTurnMessage final : public EventMessage {
public:

    inline explicit EndTurnMessage(int turn)
            : EventMessage("end", {turn})
    {
    }
};

#endif // AIC18_CLIENT_CPP_END_TURN_MESSAGE_H