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

//API:
    int getCasterId() const;
    std::vector<int> getTargetHeroIds() const;
    Cell getStartCell() const;
    Cell getEndCell() const;
    AbilityName getAbilityName() const;

private:
    int _casterId;
    std::vector<int> _targetHeroId;
    Cell _startCell;
    Cell _endCell;
    AbilityName _abilityName;

    friend class TurnMessage;
};


#endif //AIC19_CLIENT_CPP_CASTABILITY_H
