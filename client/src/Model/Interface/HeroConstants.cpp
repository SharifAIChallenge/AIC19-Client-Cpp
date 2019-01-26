#include "HeroConstants.h"


HeroName HeroConstants::get_name() const {
    return _name;
}

HeroConstants::~HeroConstants() {// clear the AbilityNames vector
    for (std::vector<AbilityName *>::iterator it = _abilityNames.begin() ; it != _abilityNames.end(); ++it)
    {
        delete (*it);
    }
    _abilityNames.clear();
}

void HeroConstants::set_name(HeroName name) {
    HeroConstants::_name = name;
}

HeroName &HeroConstants::name() {
    return _name;
}

HeroName HeroConstants::name() const {
    return _name;
}

const std::vector<AbilityName *> &HeroConstants::get_abilityNames() const {
    return _abilityNames;
}

void HeroConstants::set_abilityNames(const std::vector<AbilityName *> &abilityName) {
    HeroConstants::_abilityNames = abilityName;
}

int HeroConstants::get_maxHP() const {
    return _maxHP;
}

void HeroConstants::set_maxHP(int maxHP) {
    HeroConstants::_maxHP = maxHP;
}

int &HeroConstants::maxHP() {
    return _maxHP;
}

int HeroConstants::maxHP() const {
    return _maxHP;
}

int HeroConstants::get_moveAPCost() const {
    return _moveAPCost;
}

void HeroConstants::set_moveAPCost(int moveAPCost) {
    HeroConstants::_moveAPCost = moveAPCost;
}

int &HeroConstants::moveAPCost() {
    return _moveAPCost;
}

int HeroConstants::moveAPCost() const {
    return _moveAPCost;
}
