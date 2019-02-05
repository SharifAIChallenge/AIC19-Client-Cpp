//
// Created by dot_blue on 1/23/19.
//

#include "Ability.h"
//----------abilityConstants-----------
AbilityConstants &Ability::abilityConstants() {
    return _abilityConstants;
}

AbilityConstants Ability::getAbilityConstants() const {
    return _abilityConstants;
}
//--------------remCooldown------------
int &Ability::remCooldown() {
    return _remCooldown;
}

int Ability::getRemCooldown() const {
    return _remCooldown;
}

AbilityName Ability::abilityName() const {
    return _abilityConstants.getAbilityName();
}

AbilityType Ability::type() const {
    return _abilityConstants.getType();
}

int Ability::range() const {
    return _abilityConstants.getRange();
}

int Ability::APCost() const {
    return _abilityConstants.getAPCost();
}

int Ability::cooldown() const {
    return _abilityConstants.getCooldown();
}

int Ability::areaOfEffect() const {
    return _abilityConstants.getAreaOfEffect();
}

int Ability::power() const {
    return _abilityConstants.getPower();
}

bool Ability::isLobbing() const {
    return _abilityConstants.isLobbing();
}
