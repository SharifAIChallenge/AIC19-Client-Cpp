
#include "Enumerations.h"


AbilityName convert_abilityName_from_string(std::string str_abilityName){
    if(str_abilityName == "HEAL_FOR_THE_GREATER_GOOD")
        return AbilityName::HEAL_FOR_THE_GREATER_GOOD;
    if(str_abilityName == "kill")
        return AbilityName::kill;
    if(str_abilityName == "heal")
        return AbilityName::heal;
    if(str_abilityName == "suicide")
        return AbilityName::suicide;
    if(str_abilityName == "attack")
        return AbilityName::attack;
    if(str_abilityName == "dodge")
        return AbilityName::dodge;
    throw std::string("convert_abilityName_to_string:Wrong string input");
}

std::string abilityName_to_string(AbilityName _abilityName) {
    if(_abilityName == AbilityName::HEAL_FOR_THE_GREATER_GOOD)
        return "HEAL_FOR_THE_GREATER_GOOD";
    if(_abilityName == AbilityName::kill)
        return "kill";
    if(_abilityName == AbilityName::heal)
        return "heal";
    if(_abilityName == AbilityName::suicide)
        return "suicide";
    if(_abilityName == AbilityName::attack)
        return "attack";
    if(_abilityName == AbilityName::dodge)
        return "dodge";
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


