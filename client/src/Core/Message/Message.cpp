#include "Message.h"

#include <sstream>
#include <algorithm>

Message::Message(std::string&& string_form) {
    std::istringstream stream(std::move(string_form));
    stream >> m_root;
}

std::string Message::to_string() const {
    static Json::StreamWriterBuilder builder;
    builder["indentation"] = "";

    return Json::writeString(builder, m_root);
}

Message::Message(const std::string& name, const std::vector<Json::Value>& args) {
    set_name(name);
    set_args(args);
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
