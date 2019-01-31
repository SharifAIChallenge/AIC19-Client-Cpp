#ifndef AIC18_CLIENT_CPP_ENUMERATIONS_H
#define AIC18_CLIENT_CPP_ENUMERATIONS_H

#include "string"

enum AbilityName//TODO Complete these enums (if you updated this please update the function below)
{
    HEAL_FOR_THE_GREATER_GOOD
};

AbilityName convert_abilityName_from_string(std::string str_abilityName);
//-------------------------------------------
enum AbilityType
{
    HEAL,DODGE,ATTACK
};
AbilityType convert_abilityType_from_string(std::string str_abilityType);
//-------------------------------------------
enum HeroName//TODO Complete these enums (if you updated this please update the function below)
{
    HEALER
};
HeroName convert_heroName_from_string(std::string str_heroname);
//-------------------------------------------
enum Direction
{
    UP, DOWN, LEFT, RIGHT, NULL_DIRECTION//TODO check if this is okay
};

enum Phase
{
    PICK,MOVE,ACTION
};
Phase convert_phase_from_string(std::string str_phase);

#endif //AIC18_CLIENT_CPP_ENUMERATIONS_H
