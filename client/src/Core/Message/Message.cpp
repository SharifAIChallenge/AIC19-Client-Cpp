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
