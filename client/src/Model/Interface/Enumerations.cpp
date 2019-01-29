
#include "Enumerations.h"


AbilityName convert_abilityName_from_string(std::string str_ability){
    if(str_ability == "HEAL_FOR_THE_GREATER_GOOD"){
        return AbilityName::HEAL_FOR_THE_GREATER_GOOD;
    }
    throw std::string("convert_abilityName_to_string:Wrong string input");
}

HeroName convert_heroName_from_string(std::string str_heroname){
    if(str_heroname == "HEALER"){
        return HeroName::HEALER;
    }
    throw std::string("convert_heroName_to_string:Wrong string input");
}

Phase convert_phase_from_string(std::string str_phase) {
    if(str_phase == "PICK")
        return Phase::PICK;
    if(str_phase == "MOVE")
        return Phase::MOVE;
    if(str_phase == "MOVE")
        return Phase::ACTION;
    throw std::string("convert_phase_from_string:Wrong string input");
}

