
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
    if(str_abilityName == "GUARDIAN_ATTACK")
        return AbilityName::GUARDIAN_ATTACK;
    if(str_abilityName == "GUARDIAN_DODGE")
        return AbilityName::GUARDIAN_DODGE;
    if(str_abilityName == "GUARDIAN_FORTIFY")
        return AbilityName::GUARDIAN_FORTIFY;
    if(str_abilityName == "SHADOW_ATTACK")
        return AbilityName::SHADOW_ATTACK;
    if(str_abilityName == "SHADOW_DODGE")
        return AbilityName::SHADOW_DODGE;
    if(str_abilityName == "SHADOW_SLASH")
        return AbilityName::SHADOW_SLASH;
    throw std::string("convert_abilityName_to_string:Wrong string input");
}

std::string AbilityName_to_string(AbilityName _abilityName) {
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
        case AbilityName::GUARDIAN_ATTACK:
            return "GUARDIAN_ATTACK";
        case AbilityName::GUARDIAN_DODGE:
            return "GUARDIAN_DODGE";
        case AbilityName::GUARDIAN_FORTIFY:
            return "GUARDIAN_FORTIFY";
        case AbilityName::SHADOW_ATTACK:
            return "SHADOW_ATTACK";
        case AbilityName::SHADOW_SLASH:
            return "SHADOW_SLASH";
        case AbilityName::SHADOW_DODGE:
            return "SHADOW_DODGE";
    }
    throw std::string("AbilityName_to_string:Wrong AbilityName input");
}

HeroName convert_heroName_from_string(std::string str_heroname){
    if(str_heroname == "HEALER")
        return HeroName::HEALER;
    if(str_heroname == "SENTRY")
        return HeroName::SENTRY;
    if(str_heroname == "BLASTER")
        return HeroName::BLASTER;
    if(str_heroname == "GUARDIAN")
        return HeroName::GUARDIAN;
    if(str_heroname == "SHADOW")
        return HeroName::SHADOW;

    throw std::string("convert_heroName_to_string:Wrong string input");
}

std::string HeroName_to_string(HeroName _heroname) {
    switch(_heroname){
        case HeroName::HEALER:
            return "HEALER";
        case HeroName::BLASTER:
            return "BLASTER";
        case HeroName::SENTRY:
            return "SENTRY";
        case HeroName::GUARDIAN:
            return "GUARDIAN";
        case HeroName::SHADOW:
            return "SHADOW";
    }
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
    if(str_abilityType == "DEFENSIVE")
        return AbilityType::DEFENSIVE;
    if(str_abilityType == "DODGE")
        return AbilityType::DODGE;
    if(str_abilityType == "OFFENSIVE")
        return AbilityType::OFFENSIVE;
    throw std::string("convert_abilityType_from_string:Wrong string input");
}

std::string AbilityType_to_string(AbilityType _abilityType) {
    switch(_abilityType){
        case AbilityType::DEFENSIVE:
            return "DEFENSIVE";
        case AbilityType::DODGE:
            return "DODGE";
        case AbilityType::OFFENSIVE:
            return "OFFENSIVE";
    }
    throw std::string("AbilityType_to_string:Wrong AbilityType input");
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



