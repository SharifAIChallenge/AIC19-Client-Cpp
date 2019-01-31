//
// Created by dot_blue on 1/23/19.
//

#include "Ability.h"
//----------abilityConstants-----------
AbilityConstants &Ability::abilityConstants() {
    return _abilityConstants;
}

AbilityConstants Ability::abilityConstants() const {
    return _abilityConstants;
}
//--------------remCooldown------------
int &Ability::remCooldown() {
    return _remCooldown;
}

int Ability::remCooldown() const {
    return _remCooldown;
}

AbilityName Ability::abilityName() const {
    return _abilityConstants.abilityName();
}

std::string Ability::type() const {
    return _abilityConstants.type();
}

int Ability::range() const {
    return _abilityConstants.range();
}

int Ability::APCost() const {
    return _abilityConstants.APCost();
}

int Ability::cooldown() const {
    return _abilityConstants.cooldown();
}

int Ability::areaOfEffect() const {
    return _abilityConstants.areaOfEffect();
}

int Ability::power() const {
    return _abilityConstants.power();
}

bool Ability::isLobbing() const {
    return _abilityConstants.isLobbing();
}

bool Ability::isPiercing() const {
    return _abilityConstants.isPiercing();
}
