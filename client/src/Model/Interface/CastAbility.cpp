//
// Created by dot_blue on 1/29/19.
//

#include "CastAbility.h"

int &CastAbility::casterId() {
    return _casterId;
}

int CastAbility::casterId() const {
    return _casterId;
}

std::vector<int> &CastAbility::targetHeroId() {
    return _targetHeroId;
}

std::vector<int> CastAbility::targetHeroId() const {
    return _targetHeroId;
}

Cell &CastAbility::startCell() {
    return _startCell;
}

Cell CastAbility::startCell() const {
    return _startCell;
}

Cell &CastAbility::endCell() {
    return _endCell;
}

Cell CastAbility::encCell() const {
    return _endCell;
}

AbilityName &CastAbility::abilityName() {
    return _abilityName;
}

AbilityName CastAbility::abilityName() const {
    return _abilityName;
}
