#include "TurnMessage.h"

TurnMessage::TurnMessage(std::string&& string_form)
        : Message(std::move(string_form))
{
}
