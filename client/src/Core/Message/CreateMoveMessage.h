#ifndef AIC19_CLIENT_CPP_CREATEMOVEMESSAGE_H
#define AIC19_CLIENT_CPP_CREATEMOVEMESSAGE_H


#include "EventMessage.h"

class CreateMoveMessage final: public EventMessage{
public:

    inline explicit CreateMoveMessage(int HeroId,Json::Value _directionStrings, int currentTurn, int movePhaseNum):
            EventMessage("move",{HeroId,_directionStrings, currentTurn, movePhaseNum})
    {
    }

};


#endif //AIC19_CLIENT_CPP_CREATEMOVEMESSAGE_H
