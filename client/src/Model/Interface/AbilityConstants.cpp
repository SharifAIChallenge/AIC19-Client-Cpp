#include "AbilityConstants.h"

//-----------AbilityName----------------
AbilityName AbilityConstants::get_abilityName() const {
    return _abilityName;
}

void AbilityConstants::set_abilityName(AbilityName _abilityName) {
    AbilityConstants::_abilityName = _abilityName;
}

AbilityName& AbilityConstants::abilityName() {
    return _abilityName;
}

AbilityName AbilityConstants::abilityName() const {
    return _abilityName;
}
//---------------type------------------
const std::string &AbilityConstants::get_type() const {
    return _type;
}

void AbilityConstants::set_type(const std::string &_type) {
    AbilityConstants::_type = _type;
}

std::string& AbilityConstants::type() {
    return _type;
}

std::string AbilityConstants::type() const{
    return _type;
}
//---------------range-----------------
int AbilityConstants::get_range() const {
    return _range;
}

void AbilityConstants::set_range(int _range) {
    AbilityConstants::_range = _range;
}

int &AbilityConstants::range() {
    return _range;
}

int AbilityConstants::range() const {
    return _range;
}
//-------------APCost------------------
int AbilityConstants::get_APCost() const {
    return _APCost;
}

void AbilityConstants::set_APCost(int _APCost) {
    AbilityConstants::_APCost = _APCost;
}

int &AbilityConstants::APCost() {
    return _APCost;
}

int AbilityConstants::APCost() const {
    return _APCost;
}
//-------------cooldown----------------
int AbilityConstants::get_cooldown() const {
    return _cooldown;
}

void AbilityConstants::set_cooldown(int _cooldown) {
    AbilityConstants::_cooldown = _cooldown;
}

int &AbilityConstants::cooldown() {
    return _cooldown;
}

int AbilityConstants::cooldown() const {
    return _cooldown;
}
//-----------areaOfEffect--------------
int AbilityConstants::get_areaOfEffect() const {
    return _areaOfEffect;
}

void AbilityConstants::set_areaOfEffect(int _areaOfEffect) {
    AbilityConstants::_areaOfEffect = _areaOfEffect;
}

int &AbilityConstants::areaOfEffect() {
    return _areaOfEffect;
}

int AbilityConstants::areaOfEffect() const {
    return _areaOfEffect;
}
//---------------power-----------------
int AbilityConstants::get_power() const {
    return _power;
}

void AbilityConstants::set_power(int _power) {
    AbilityConstants::_power = _power;
}

int &AbilityConstants::power() {
    return _power;
}

int AbilityConstants::power() const {
    return _power;
}
//--------------isLobbing--------------
bool AbilityConstants::is_Lobbing() const {
    return _isLobbing;
}

void AbilityConstants::set_Lobbing(bool _isLobbing) {
    AbilityConstants::_isLobbing = _isLobbing;
}

bool &AbilityConstants::isLobbing() {
    return _isLobbing;
}

bool AbilityConstants::isLobbing() const {
    return _isLobbing;
}
//------------isPiercing---------------
bool AbilityConstants::is_Piercing() const {
    return _isPiercing;
}

void AbilityConstants::set_Piercing(bool _isPiercing) {
    AbilityConstants::_isPiercing = _isPiercing;
}

bool &AbilityConstants::isPiercing() {
    return _isPiercing;
}

bool AbilityConstants::isPiercing() const {
    return _isPiercing;
}
