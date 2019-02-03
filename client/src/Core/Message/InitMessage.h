#ifndef AIC19_CLIENT_CPP_INIT_MESSAGE_H
#define AIC19_CLIENT_CPP_INIT_MESSAGE_H

#include <Model/Interface/GameConstants.h>
#include <Model/Interface/Map.h>
#include <Model/Interface/HeroConstants.h>
#include <Model/Interface/AbilityConstants.h>

#include "Message.h"
#include "ParseError.h"
#include <vector>
#include <Model/Interface/World.h>

class InitMessage final : public Message {
public:

    explicit InitMessage(Json::Value&& root);

    explicit InitMessage(std::string&& json_form);

//    GameConstants parse_gameConstants();
//
//    Map parse_map();
//
//    std::vector<HeroConstants *> parse_heroConstants();
//
//    std::vector<AbilityConstants *> parse_abilityConstants();

    void update_world(World* _world);

private:
//    HeroName give_HeroNameEnum(std::string HeroName);
//    AbilityName give_AbilityName(std::string AbilityName);


};

#endif // AIC19_CLIENT_CPP_INIT_MESSAGE_H
