//
// Created by dot_blue on 1/29/19.
//

#include "CastAbility.h"

int CastAbility::getCasterId() const {
    return _casterId;
}

std::vector<int> CastAbility::getTargetHeroIds() const {
    return _targetHeroId;
}

Cell CastAbility::getStartCell() const {
    return _startCell;
}

Cell CastAbility::getEndCell() const {
    return _endCell;
}

AbilityName CastAbility::getAbilityName() const {
    return _abilityName;
}
