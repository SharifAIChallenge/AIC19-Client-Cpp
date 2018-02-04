#ifndef AIC18_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
#define AIC18_CLIENT_CPP_AUTHENTICATION_MESSAGE_H

#include "Message.h"

class AuthenticationMessage : public Message {
public:

    inline AuthenticationMessage(const std::string& token, const std::string& name)
            : Message()
    {
        m_root["args"].append(token);
        m_root["name"] = name;
    }
};

#endif // AIC18_CLIENT_CPP_AUTHENTICATION_MESSAGE_H
