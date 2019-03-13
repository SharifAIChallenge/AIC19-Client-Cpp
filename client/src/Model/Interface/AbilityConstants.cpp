#include "AbilityConstants.h"


//------------constructor---------------
AbilityConstants::AbilityConstants(bool _isNull): isNull(_isNull) {
    if(_isNull){
        this->_range = -1;
    }
}

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
//--------------isPiercing--------------
bool AbilityConstants::isPiercing() const {
    return _isPiercing;
}

//single tone:
AbilityConstants AbilityConstants::NULL_ABILITY_CONSTANTS(true);

bool AbilityConstants::operator==(const AbilityConstants & _abilityConst) {
    return ((this->_abilityName == _abilityConst._abilityName) &&
            (this->_type == _abilityConst._type) &&
            (this->_range == _abilityConst._range) &&
            (this->_APCost == _abilityConst._APCost) &&
            (this->_cooldown == _abilityConst._cooldown) &&
            (this->_areaOfEffect == _abilityConst._areaOfEffect) &&
            (this->_power == _abilityConst._power) &&
            (this->_isLobbing == _abilityConst._isLobbing) &&
            !this->isNull &&
            !_abilityConst.isNull)
            ||(_abilityConst.isNull && this->isNull);
}
