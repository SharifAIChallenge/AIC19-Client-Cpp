#ifndef AIC18_CLIENT_CPP_PICKMESSAGE_H
#define AIC18_CLIENT_CPP_PICKMESSAGE_H


#include <Model/Interface/Game.h>
#include "Message.h"
#include "ParseError.h"

class PickMessage final: public Message {
public:
    explicit PickMessage(Json::Value&& root);

    explicit PickMessage(std::string&& json_form);

    void update_game(Game* _game);

};



#endif //AIC18_CLIENT_CPP_PICKMESSAGE_H
