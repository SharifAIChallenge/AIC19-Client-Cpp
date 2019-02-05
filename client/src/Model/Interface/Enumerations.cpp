
#include "Enumerations.h"


AbilityName convert_abilityName_from_string(std::string str_abilityName){
    if(str_abilityName == "SENTRY_ATTACK")
        return AbilityName::SENTRY_ATTACK;
    if(str_abilityName == "SENTRY_DODGE")
        return AbilityName::SENTRY_DODGE;
    if(str_abilityName == "SENTRY_RAY")
        return AbilityName::SENTRY_RAY;
    if(str_abilityName == "BLASTER_ATTACK")
        return AbilityName::BLASTER_ATTACK;
    if(str_abilityName == "BLASTER_DODGE")
        return AbilityName::BLASTER_DODGE;
    if(str_abilityName == "BLASTER_BOMB")
        return AbilityName::BLASTER_BOMB;
    if(str_abilityName == "HEALER_ATTACK")
        return AbilityName::HEALER_ATTACK;
    if(str_abilityName == "HEALER_DODGE")
        return AbilityName::HEALER_DODGE;
    if(str_abilityName == "HEALER_HEAL")
        return AbilityName::HEALER_HEAL;
    if(str_abilityName == "GAURDIAN_ATTACK")
        return AbilityName::GAURDIAN_ATTACK;
    if(str_abilityName == "GAURDIAN_DODGE")
        return AbilityName::GAURDIAN_DODGE;
    if(str_abilityName == "GAURDIAN_FORTIFY")
        return AbilityName::GAURDIAN_FORTIFY;
    throw std::string("convert_abilityName_to_string:Wrong string input");
}

std::string abilityName_to_string(AbilityName _abilityName) {
    switch(_abilityName){
        case AbilityName::SENTRY_ATTACK:
            return "SENTRY_ATTACK";
        case AbilityName::SENTRY_DODGE:
            return "SENTRY_DODGE";
        case AbilityName::SENTRY_RAY:
            return "SENTRY_RAY";
        case AbilityName::BLASTER_ATTACK:
            return "BLASTER_ATTACK";
        case AbilityName::BLASTER_DODGE:
            return "BLASTER_DODGE";
        case AbilityName::BLASTER_BOMB:
            return "BLASTER_BOMB";
        case AbilityName::HEALER_ATTACK:
            return "HEALER_ATTACK";
        case AbilityName::HEALER_DODGE:
            return "HEALER_DODGE";
        case AbilityName::HEALER_HEAL:
            return "HEALER_HEAL";
        case AbilityName::GAURDIAN_ATTACK:
            return "GAURDIAN_ATTACK";
        case AbilityName::GAURDIAN_DODGE:
            return "GAURDIAN_DODGE";
        case AbilityName::GAURDIAN_FORTIFY:
            return "GAURDIAN_FORTIFY";
    }
    throw std::string("abilityName_to_string:Wrong AbilityName input");
}

HeroName convert_heroName_from_string(std::string str_heroname){
    if(str_heroname == "HEALER")
        return HeroName::HEALER;
    if(str_heroname == "Ruhollah")
        return HeroName::Ruhollah;
    if(str_heroname == "Ali")
        return HeroName::Ali;
    if(str_heroname == "Omid")
        return HeroName::Omid;

    throw std::string("convert_heroName_to_string:Wrong string input");
}


std::string HeroName_to_string(HeroName _heroname) {
    if(_heroname == HeroName::HEALER)
        return "HEALER";
    if(_heroname == HeroName::Ruhollah)
        return "Ruhollah";
    if(_heroname == HeroName::Ali)
        return "Ali";
    if(_heroname == HeroName::Omid)
        return "Omid";
    throw std::string("HeroName_to_string:Wrong HeroName input");
}


Phase convert_phase_from_string(std::string str_phase) {
    if(str_phase == "PICK")
        return Phase::PICK;
    if(str_phase == "MOVE")
        return Phase::MOVE;
    if(str_phase == "ACTION")
        return Phase::ACTION;
    throw std::string("convert_phase_from_string:Wrong string input");
}

AbilityType convert_abilityType_from_string(std::string str_abilityType) {
    if(str_abilityType == "HEAL")
        return AbilityType::HEAL;
    if(str_abilityType == "DODGE")
        return AbilityType::DODGE;
    if(str_abilityType == "ATTACK")
        return AbilityType::ATTACK;
    throw std::string("convert_abilityType_from_string:Wrong string input");
}

std::string Direction_to_string(Direction _direction) {
    switch(_direction){
        case Direction::UP:
            return "UP";
        case Direction::DOWN:
            return "DOWN";
        case Direction::LEFT:
            return "LEFT";
        case Direction::RIGHT:
            return "RIGHT";
    }
    throw std::string("Direction_to_string:Wrong Direction input");
}


