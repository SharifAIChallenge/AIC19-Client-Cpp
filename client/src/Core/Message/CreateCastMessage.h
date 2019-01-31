#ifndef AIC18_CLIENT_CPP_CREATECASTMESSAGE_H
#define AIC18_CLIENT_CPP_CREATECASTMESSAGE_H


#include "EventMessage.h"


class CreateCastMessage final: public EventMessage{
public:
    inline explicit CreateCastMessage(int HeroId, std::string AbilityName,int Cellrow, int Cellcolumn):
            EventMessage("cast",{HeroId,AbilityName,Cellrow,Cellcolumn})
    {
    }

};

#endif //AIC18_CLIENT_CPP_CREATECASTMESSAGE_H
