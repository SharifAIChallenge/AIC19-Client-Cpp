#ifndef AIC19_CLIENT_CPP_SHUTDOWN_MESSAGE_H
#define AIC19_CLIENT_CPP_SHUTDOWN_MESSAGE_H

#include "Message.h"
#include "ParseError.h"

class ShutdownMessage : public Message {
public:

    explicit ShutdownMessage(Json::Value&& root)
            : Message(std::move(root))
    {
        if (Message::get_name() != "shutdown")
            throw ParseError("Invalid shutdown message");
    }

    explicit ShutdownMessage(std::string&& json_form)
            : Message(std::move(json_form))
    {
        if (Message::get_name() != "shutdown")
            throw ParseError("Invalid shutdown message");
    }
};

#endif // AIC19_CLIENT_CPP_SHUTDOWN_MESSAGE_H