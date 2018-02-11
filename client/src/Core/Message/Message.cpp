#include "Message.h"

#include <sstream>
#include <algorithm>
#include <memory>

#include <Utility/Utility.h>

#include "ParseError.h"

#include "InitMessage.h"
#include "TurnMessage.h"
#include "ShutdownMessage.h"

Message::Message(Json::Value&& root)
        : m_root(std::move(root))
{
}

Message::Message(std::string&& json_form) {
    std::istringstream stream(json_form);
    stream >> m_root;
}

Message::Message(const std::string& name, const std::vector<Json::Value>& args) {
    set_name(name);
    set_args(args);
}

std::string Message::to_string() const {
    static Json::StreamWriterBuilder builder;
    builder["indentation"] = "";

    return Json::writeString(builder, m_root);
}

void Message::set_name(const std::string& name) {
    m_root["name"] = name;
}

std::string Message::get_name() const {
    return m_root["name"].asString();
}

void Message::set_args(const std::vector<Json::Value>& args) {
    m_root["args"].clear();
    for (const Json::Value& arg : args)
        m_root["args"].append(arg);
}

Json::Value& Message::get_mutable_args() {
    return m_root["args"];
}

Json::Value Message::get_args() const {
    return m_root["args"];
}

std::unique_ptr<Message> Message::CreateFromJsonString(const std::string& string_form) {
    Json::Value root;

    std::istringstream stream(string_form);
    stream >> root;

    if (root["name"] == "init")
        return make_unique<InitMessage>(std::move(root));
    else if (root["name"] == "turn")
        return make_unique<TurnMessage>(std::move(root));
    else if (root["name"] == "shutdown")
        return make_unique<ShutdownMessage>(std::move(root));

    throw ParseError("Unknown message type");
}
