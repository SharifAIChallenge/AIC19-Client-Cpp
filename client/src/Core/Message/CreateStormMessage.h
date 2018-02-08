#ifndef AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H

#include <Model/Point.h>
#include "EventMessage.h"

class CreateStormMessage final : public EventMessage {
public:

    inline explicit CreateStormMessage(Point location)
            : EventMessage("s", {location.x(), location.y()})
    {
    }
};

#endif // AIC18_CLIENT_CPP_CREATE_STORM_MESSAGE_H
