//
// Created by dot_blue on 1/23/19.
//

#include "Ability.h"
//--------------remCooldown------------
int Ability::getRemCooldown() const {
    return _remCooldown;
}

AbilityName Ability::getName() const {
    return _abilityConstants.getName();
}

AbilityType Ability::getType() const {
    return _abilityConstants.getType();
}

int Ability::getRange() const {
    return _abilityConstants.getRange();
}

int Ability::getAPCost() const {
    return _abilityConstants.getAPCost();
}

int Ability::getCooldown() const {
    return _abilityConstants.getCooldown();
}

int Ability::getAreaOfEffect() const {
    return _abilityConstants.getAreaOfEffect();
}

int Ability::getPower() const {
    return _abilityConstants.getPower();
}

bool Ability::isLobbing() const {
    return _abilityConstants.isLobbing();
}

bool Ability::isReady() const {
    return _remCooldown == 0;
}

AbilityConstants Ability::getAbilityConstants() const {
    return _abilityConstants;
}
