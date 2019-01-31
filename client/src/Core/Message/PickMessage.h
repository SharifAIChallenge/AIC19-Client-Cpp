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

HeroName Hero::name() const {
    return _heroConstants.name();
}

const std::vector<AbilityName> &Hero::abilityNames() const {
    return _heroConstants.get_abilityNames();
}

int Hero::maxHP() const {
    return _heroConstants.maxHP();
}

int Hero::moveAPCost() const {
    return _heroConstants.moveAPCost();
}

int Hero::remainingRespawnTime() const {
    return _heroConstants.remainingRespawnTime();
}


#endif //AIC18_CLIENT_CPP_PICKMESSAGE_H
