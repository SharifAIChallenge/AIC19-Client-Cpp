#ifndef AIC19_CLIENT_CPP_END_TURN_MESSAGE_H
#define AIC19_CLIENT_CPP_END_TURN_MESSAGE_H

#include "EventMessage.h"

class EndTurnMessage final : public EventMessage {
public:

    inline explicit EndTurnMessage(int turn)
            : EventMessage("end", {turn})
    {
    }
};

#endif // AIC19_CLIENT_CPP_END_TURN_MESSAGE_H