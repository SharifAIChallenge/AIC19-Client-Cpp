#ifndef AIC19_CLIENT_CPP_TURNMESSAGE_H
#define AIC19_CLIENT_CPP_TURNMESSAGE_H

#include <Model/Interface/Cell.h>
#include <Model/Interface/Hero.h>
#include <Model/Interface/CastAbility.h>
#include <Model/Interface/World.h>
#include "Message.h"
#include "ParseError.h"

class TurnMessage final: public Message {
public:
    explicit TurnMessage(Json::Value&& root);

    explicit TurnMessage(std::string&& json_form);

//    int parse_myScore();
//
//    int parse_oppScore();
//
//    std::string parse_currentPhase();
//
//    int parse_currentTurn();

//    std::vector<std::vector<Cell *>> parse_map_cells();

    void update_game(World* _game);

//    std::vector<Hero *> parse_myHeros();
//
//    std::vector<Hero *> parse_oppHeros();
//
//    std::vector<CastAbility *> parse_myCastedAbilities();
//
//    std::vector<CastAbility *> parse_oppCastedAbilities();

private:
//    Hero parse_hero_from_JSON(Json::Value hero_DATA);

};


#endif //AIC19_CLIENT_CPP_TURNMESSAGE_H
