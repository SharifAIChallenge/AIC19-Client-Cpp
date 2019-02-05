#include "HeroConstants.h"


HeroConstants::~HeroConstants() {

}

HeroConstants::HeroConstants(bool _isNull): isNull(_isNull) {}


HeroName HeroConstants::getName() const {
    return _name;
}

std::vector<AbilityName> HeroConstants::getAbilityNames() const {
    return _abilityNames;
}

int HeroConstants::getMaxHP() const {
    return _maxHP;
}

int HeroConstants::getMoveAPCost() const {
    return _moveAPCost;
}

int HeroConstants::getRespawnTime() const {
    return _remainingRespawnTime;
}

HeroConstants HeroConstants::NULL_HERO_CONSTANT(true);
