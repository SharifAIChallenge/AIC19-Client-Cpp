
#include "Enumerations.h"


AbilityName convert_abilityName_from_string(std::string str_abilityName){
    if(str_abilityName == "HEAL_FOR_THE_GREATER_GOOD"){
        return AbilityName::HEAL_FOR_THE_GREATER_GOOD;
    }
    throw std::string("convert_abilityName_to_string:Wrong string input");
}

std::string abilityName_to_string(AbilityName _abilityName) {
    if(_abilityName == AbilityName::HEAL_FOR_THE_GREATER_GOOD)
        return "HEAL_FOR_THE_GREATER_GOOD";
    throw std::string("abilityName_to_string:Wrong AbilityName input");
}

HeroName convert_heroName_from_string(std::string str_heroname){
    if(str_heroname == "HEALER"){
        return HeroName::HEALER;
    }
    throw std::string("convert_heroName_to_string:Wrong string input");
}


std::string HeroName_to_string(HeroName _heroname) {
    if(_heroname == HeroName::HEALER)
        return "HEALER";
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


