#ifndef AIC19_CLIENT_CPP_CREATEPICKMESSAGE_H
#define AIC19_CLIENT_CPP_CREATEPICKMESSAGE_H

#include "EventMessage.h"

class CreatePickMessage final: public EventMessage{
public:

    inline explicit CreatePickMessage(std::string HeroNameStr,int currentTurn):
            EventMessage("pick",{HeroNameStr,currentTurn})
    {
    }

};

#endif //AIC19_CLIENT_CPP_CREATEPICKMESSAGE_H
