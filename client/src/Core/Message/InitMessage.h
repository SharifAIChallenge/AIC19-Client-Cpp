#ifndef AIC18_CLIENT_CPP_INIT_MESSAGE_H
#define AIC18_CLIENT_CPP_INIT_MESSAGE_H

#include <Model/Interface/GameConstants.h>
#include <Model/Interface/Map.h>
#include <Model/Interface/HeroConstants.h>
#include <Model/Interface/AbilityConstants.h>

#include "Message.h"
#include "ParseError.h"
#include <vector>

class InitMessage final : public Message {
public:

    explicit InitMessage(Json::Value&& root);

    explicit InitMessage(std::string&& json_form);

    GameConstants parse_gameConstants();

    Map parse_map();

    std::vector<HeroConstants *> parse_heroConstants();

    std::vector<AbilityConstants *> parse_abilityConstants();

private:
//    HeroName give_HeroNameEnum(std::string HeroName);
//    AbilityName give_AbilityName(std::string AbilityName);


};

#endif // AIC18_CLIENT_CPP_INIT_MESSAGE_H
