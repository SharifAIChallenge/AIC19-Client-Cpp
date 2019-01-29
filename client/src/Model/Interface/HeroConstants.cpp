#include "HeroConstants.h"


HeroConstants::~HeroConstants() {

}

HeroConstants::HeroConstants(bool _isNull):HeroConstants(),
                                           isNull(_isNull) {}


HeroName &HeroConstants::name() {
    return _name;
}

HeroName HeroConstants::name() const {
    return _name;
}

const std::vector<AbilityName> &HeroConstants::get_abilityNames() const {
    return _abilityNames;
}

void HeroConstants::set_abilityNames(const std::vector<AbilityName> &abilityName) {
    HeroConstants::_abilityNames = abilityName;
}

int &HeroConstants::maxHP() {
    return _maxHP;
}

int HeroConstants::maxHP() const {
    return _maxHP;
}

int &HeroConstants::moveAPCost() {
    return _moveAPCost;
}

int HeroConstants::moveAPCost() const {
    return _moveAPCost;
}

int &HeroConstants::remainingRespawnTime() {
    return _remainingRespawnTime;
}

int HeroConstants::remainingRespawnTime() const {
    return _remainingRespawnTime;
}

HeroConstants HeroConstants::NULL_HERO_CONSTANT(true);
