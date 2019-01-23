//
// Created by dot_blue on 1/23/19.
//

#include "Ability.h"
//----------abilityConstants-----------
const AbilityConstants &Ability::get_abilityConstants() const {
    return _abilityConstants;
}

void Ability::set_abilityConstants(const AbilityConstants &_abilityConstants) {
    Ability::_abilityConstants = _abilityConstants;
}

AbilityConstants &Ability::abilityConstants() {
    return _abilityConstants;
}

AbilityConstants Ability::abilityConstants() const {
    return _abilityConstants;
}
//--------------remCooldown------------
int Ability::get_remCooldown() const {
    return _remCooldown;
}

void Ability::set_remCooldown(int _remCooldown) {
    Ability::_remCooldown = _remCooldown;
}

int &Ability::remCooldown() {
    return _remCooldown;
}

int Ability::remCooldown() const {
    return _remCooldown;
}
