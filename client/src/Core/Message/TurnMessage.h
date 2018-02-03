#ifndef AIC18_CLIENT_CPP_TURN_MESSAGE_H
#define AIC18_CLIENT_CPP_TURN_MESSAGE_H

#include "Message.h"

class TurnMessage final : public Message {
public:

    explicit TurnMessage(std::string&& string_form);
};

#endif // AIC18_CLIENT_CPP_TURN_MESSAGE_H
