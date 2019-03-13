#ifndef AIC19_CLIENT_CPP_ENUMERATIONS_H
#define AIC19_CLIENT_CPP_ENUMERATIONS_H

#include "string"

enum AbilityName// Complete these enums (if you updated this please update the function below)
{
    SENTRY_ATTACK,
    SENTRY_DODGE,
    SENTRY_RAY,
    BLASTER_ATTACK,
    BLASTER_DODGE,
    BLASTER_BOMB,
    HEALER_ATTACK,
    HEALER_DODGE,
    HEALER_HEAL,
    GUARDIAN_ATTACK,
    GUARDIAN_DODGE,
    GUARDIAN_FORTIFY,
    SHADOW_ATTACK,
    SHADOW_DODGE,
    SHADOW_SLASH
};

AbilityName convert_abilityName_from_string(std::string str_abilityName);
std::string AbilityName_to_string(AbilityName _abilityName);
//-------------------------------------------
enum AbilityType
{
    DEFENSIVE,DODGE,OFFENSIVE
};
AbilityType convert_abilityType_from_string(std::string str_abilityType);
std::string AbilityType_to_string(AbilityType _abilityType);
//-------------------------------------------
enum HeroName
{
    SENTRY,BLASTER,HEALER,GUARDIAN,SHADOW
};
HeroName convert_heroName_from_string(std::string str_heroname);
std::string HeroName_to_string(HeroName _heroname);
//-------------------------------------------
enum Direction
{
    UP, DOWN, LEFT, RIGHT, NULL_DIRECTION
};

std::string Direction_to_string(Direction _direction);

enum Phase
{
    PICK,MOVE,ACTION
};
Phase convert_phase_from_string(std::string str_phase);

#endif //AIC19_CLIENT_CPP_ENUMERATIONS_H
