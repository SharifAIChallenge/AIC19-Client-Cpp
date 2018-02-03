#ifndef AIC18_CLIENT_CPP_INIT_MESSAGE_H
#define AIC18_CLIENT_CPP_INIT_MESSAGE_H

#include "Message.h"
#include "../../Model/Map.h"

class InitMessage final : public Message {
public:

    InitMessage(std::string&& string_form);
};

#endif // AIC18_CLIENT_CPP_INIT_MESSAGE_H
