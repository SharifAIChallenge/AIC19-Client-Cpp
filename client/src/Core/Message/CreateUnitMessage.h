#ifndef AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
#define AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H

#include <Model/Unit.h>
#include "EventMessage.h"

class CreateUnitMessage final : public EventMessage {
public:

    inline CreateUnitMessage(UnitType type, int path_index)
            : EventMessage("cu", {type == UnitType::LIGHT ? "l" : "h",
                                  path_index})
    {
    }

};

#endif // AIC18_CLIENT_CPP_CREATE_UNIT_MESSAGE_H
