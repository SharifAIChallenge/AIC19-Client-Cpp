#include "InitMessage.h"

InitMessage::InitMessage(std::string&& string_form)
        : Message(std::move(string_form))
{
}
