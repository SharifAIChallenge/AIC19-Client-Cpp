#ifndef AIC19_CLIENT_CPP_EVENT_MESSAGE_H
#define AIC19_CLIENT_CPP_EVENT_MESSAGE_H

#include <string>
#include <vector>

#include "Message.h"

/**
 * A message indicating an event from client
 */
class EventMessage : public Message {
public:

    EventMessage() = default;
    ~EventMessage() override = default;

    EventMessage(const EventMessage&) = default;
    EventMessage& operator=(const EventMessage&) = default;

    EventMessage(EventMessage&&) = default;
    EventMessage& operator=(EventMessage&&) = default;

    /**
     * Construct an event message with the given type and args
     */
    explicit EventMessage(const std::string& type, const std::vector<Json::Value>& args);

    void set_type(const std::string& type);
    std::string get_type() const;

    void set_args(const std::vector<Json::Value>& args);
    Json::Value& get_mutable_args();
    Json::Value get_args() const;

};

#endif // AIC19_CLIENT_CPP_EVENT_MESSAGE_H