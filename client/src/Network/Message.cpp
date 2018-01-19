#include "Message.h"

#include <sstream>

Message::Message(std::string&& string_form) {
    std::istringstream stream(std::move(string_form));
    stream >> m_root;
}

std::string Message::to_string() const {
    std::ostringstream stream;
    stream << m_root;
    return stream.str();
}
