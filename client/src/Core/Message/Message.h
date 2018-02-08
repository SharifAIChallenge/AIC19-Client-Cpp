#ifndef AIC18_CLIENT_CPP_MESSAGE_H
#define AIC18_CLIENT_CPP_MESSAGE_H

#include <string>
#include <vector>

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
     * @return The message in json string form
     */
    std::string to_string() const;

protected:

    /**
     * Construct a message with the given name and no args
     */
    // TODO: explicit Message(const std::string& name);

    /**
     * Construct a message with the given name and args
     */
    Message(const std::string& name, const std::vector<Json::Value>& args);

    void set_name(const std::string& name);
    std::string get_name() const;

    void set_args(const std::vector<Json::Value>& args);
    Json::Value& get_mutable_args();
    Json::Value get_args() const;

protected:

    /// Json tree root
    Json::Value m_root;

};

#endif // AIC18_CLIENT_CPP_MESSAGE_H
