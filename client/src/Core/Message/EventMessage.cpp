#include "EventMessage.h"

EventMessage::EventMessage(const std::string& type, const std::vector<Json::Value>& args)
        : Message("event", {})
{
    set_type(type);
    set_args(args);
}

void EventMessage::set_type(const std::string& type) {
    Message::get_mutable_args()[0]["type"] = type;
}

std::string EventMessage::get_type() const {
    return Message::get_args()[0]["type"].asString();
}

void EventMessage::set_args(const std::vector<Json::Value>& args) {
    Message::get_mutable_args()[0]["args"].clear();
    Message::get_mutable_args()[0]["args"] = Json::Value(Json::arrayValue);
    for (const Json::Value& arg : args)
        Message::get_mutable_args()[0]["args"].append(arg);
}

Json::Value& EventMessage::get_mutable_args() {
    return Message::get_mutable_args()[0]["args"];
}

Json::Value EventMessage::get_args() const {
    return Message::get_args()[0]["args"];
}
