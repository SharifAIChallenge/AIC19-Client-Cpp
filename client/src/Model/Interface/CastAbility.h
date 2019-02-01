#ifndef AIC19_CLIENT_CPP_CASTABILITY_H
#define AIC19_CLIENT_CPP_CASTABILITY_H

#include <vector>
#include "Cell.h"
#include "Enumerations.h"

class CastAbility {
public:
    CastAbility() = default;
    ~CastAbility() = default;

    CastAbility(const CastAbility&) = default;
    CastAbility& operator=(const CastAbility&) = default;

    CastAbility(CastAbility&&) = default;
    CastAbility& operator=(CastAbility&&) = default;

    int& casterId();
    int casterId() const;

    std::vector<int>& targetHeroId();
    std::vector<int> targetHeroId() const;

    Cell& startCell();
    Cell startCell() const;

    Cell& endCell();
    Cell encCell() const;

    AbilityName& abilityName();
    AbilityName abilityName() const;

private:
    int _casterId;
    std::vector<int> _targetHeroId;
    Cell _startCell;
    Cell _endCell;
    AbilityName _abilityName;
};


#endif //AIC19_CLIENT_CPP_CASTABILITY_H
