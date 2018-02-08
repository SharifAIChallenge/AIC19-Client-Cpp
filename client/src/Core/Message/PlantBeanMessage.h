#ifndef AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H
#define AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H

#include <Model/Point.h>
#include "EventMessage.h"

class PlantBeanMessage final : public EventMessage {
public:

    inline explicit PlantBeanMessage(Point location)
            : EventMessage("b", {location.x(), location.y()})
    {
    }
};

#endif // AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H
