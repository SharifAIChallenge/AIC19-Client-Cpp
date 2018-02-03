#ifndef AIC18_CLIENT_CPP_MESSAGE_H
#define AIC18_CLIENT_CPP_MESSAGE_H

#include <string>

#include <json/json.h>

/**
 * A json message sent/received across the network
 */
class Message {
public:

    Message() = default;
    virtual ~Message() = default;

    Message(const Message&) = default;
    Message& operator= (const Message&) = default;

    Message(Message&&) = default;
    Message& operator= (Message&&) = default;

    /**
     * Construct a message from its string form
     */
    explicit Message(std::string&& string_form);

    /**
     * @return The message in string form
     */
    std::string to_string() const;

protected:

    /// Json tree root
    Json::Value m_root;

};

#endif // AIC18_CLIENT_CPP_MESSAGE_H
