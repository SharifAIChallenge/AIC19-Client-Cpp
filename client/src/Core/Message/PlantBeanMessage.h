#ifndef AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H
#define AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H

#include "Message.h"
#include "../../Model/Point.h"

class PlantBeanMessage final : public Message {
public:

    inline explicit PlantBeanMessage(Point location)
    : Message()
    {
        m_root["type"] = "b";
        m_root["args"].append(location.get_x());
        m_root["args"].append(location.get_y());
    }
};

#endif // AIC18_CLIENT_CPP_PLANT_BEAN_MESSAGE_H
