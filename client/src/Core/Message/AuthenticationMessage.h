#ifndef AIC19_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
#define AIC19_CLIENT_CPP_AUTHENTICATION_MESSAGE_H

#include "Message.h"

class AuthenticationMessage : public Message {
public:

    inline explicit AuthenticationMessage(const std::string& token)
            : Message("token", {token})
    {
    }
};

#endif // AIC19_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
