#ifndef AIC18_CLIENT_CPP_CREATEMOVEMESSAGE_H
#define AIC18_CLIENT_CPP_CREATEMOVEMESSAGE_H


#include "EventMessage.h"

class CreateMoveMessage final: public EventMessage{
public:

    inline explicit CreateMoveMessage(int HeroId,Json::Value _directionStrings):
            EventMessage("move",{HeroId,_directionStrings})
    {
    }

};


#endif //AIC18_CLIENT_CPP_CREATEMOVEMESSAGE_H
