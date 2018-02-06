#ifndef AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H
#define AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H

#include <Model/Point.h>
#include "Message.h"

class PlantBeanMessage final : public Message {
public:

    inline explicit PlantBeanMessage(Point location)
    : Message()
    {
        m_root["name"] = "event";
        Json::Value& args = m_root["args"][0];

        args["type"] = "b";
        args["args"].append(location.get_x());
        args["args"].append(location.get_y());
    }
};

#endif // AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H
