#include "AbilityConstants.h"


//------------constructor---------------
AbilityConstants::AbilityConstants(bool _isNull):AbilityConstants(),
                                                 isNull(_isNull) {}

//------------AbilityName---------------
AbilityName& AbilityConstants::abilityName() {
    return _abilityName;
}

AbilityName AbilityConstants::abilityName() const {
    return _abilityName;
}
//---------------type------------------
std::string& AbilityConstants::type() {
    return _type;
}

std::string AbilityConstants::type() const{
    return _type;
}
//---------------range-----------------
int &AbilityConstants::range() {
    return _range;
}

int AbilityConstants::range() const {
    return _range;
}
//-------------APCost------------------
int &AbilityConstants::APCost() {
    return _APCost;
}

int AbilityConstants::APCost() const {
    return _APCost;
}
//-------------cooldown----------------
int &AbilityConstants::cooldown() {
    return _cooldown;
}

int AbilityConstants::cooldown() const {
    return _cooldown;
}
//-----------areaOfEffect--------------
int &AbilityConstants::areaOfEffect() {
    return _areaOfEffect;
}

int AbilityConstants::areaOfEffect() const {
    return _areaOfEffect;
}
//---------------power-----------------
int &AbilityConstants::power() {
    return _power;
}

int AbilityConstants::power() const {
    return _power;
}
//--------------isLobbing--------------
bool &AbilityConstants::isLobbing() {
    return _isLobbing;
}

bool AbilityConstants::isLobbing() const {
    return _isLobbing;
}
//------------isPiercing---------------
bool &AbilityConstants::isPiercing() {
    return _isPiercing;
}

bool AbilityConstants::isPiercing() const {
    return _isPiercing;
}


//single tone:
AbilityConstants AbilityConstants::NULL_ABILITY_CONSTANTS(true);
