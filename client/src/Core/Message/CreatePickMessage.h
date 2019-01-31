#ifndef AIC18_CLIENT_CPP_CREATEPICKMESSAGE_H
#define AIC18_CLIENT_CPP_CREATEPICKMESSAGE_H

#include "EventMessage.h"

class CreatePickMessage final: public EventMessage{
public:

    inline explicit CreatePickMessage(std::string HeroNameStr):
            EventMessage("pick",{HeroNameStr})
    {
    }

};

#endif //AIC18_CLIENT_CPP_CREATEPICKMESSAGE_H
