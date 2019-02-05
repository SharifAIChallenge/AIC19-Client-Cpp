#include "AbilityConstants.h"


//------------constructor---------------
AbilityConstants::AbilityConstants(bool _isNull): isNull(_isNull) {}

//------------AbilityName---------------
AbilityName AbilityConstants::getName() const {
    return _abilityName;
}
//---------------type------------------
AbilityType AbilityConstants::getType() const{
    return _type;
}
//---------------range-----------------
int AbilityConstants::getRange() const {
    return _range;
}
//-------------APCost------------------
int AbilityConstants::getAPCost() const {
    return _APCost;
}
//-------------cooldown----------------
int AbilityConstants::getCooldown() const {
    return _cooldown;
}
//-----------areaOfEffect--------------
int AbilityConstants::getAreaOfEffect() const {
    return _areaOfEffect;
}
//---------------power-----------------
int AbilityConstants::getPower() const {
    return _power;
}
//--------------isLobbing--------------
bool AbilityConstants::isLobbing() const {
    return _isLobbing;
}

//single tone:
AbilityConstants AbilityConstants::NULL_ABILITY_CONSTANTS(true);
