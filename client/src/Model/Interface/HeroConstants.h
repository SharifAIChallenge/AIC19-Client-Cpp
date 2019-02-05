#ifndef AIC19_CLIENT_CPP_HEROCONSTANTS_H
#define AIC19_CLIENT_CPP_HEROCONSTANTS_H

#include "Enumerations.h"
#include <vector>

class HeroConstants {
public:
    HeroConstants() = default;
    ~HeroConstants();

    HeroConstants(bool _isNull);

    HeroConstants(const HeroConstants&) = default;
    HeroConstants& operator=(const HeroConstants&) = default;


    HeroName getName() const;
    std::vector<AbilityName> getAbilityNames() const;
    int getMaxHP() const;
    int getMoveAPCost() const;
    int getRespawnTime() const;

private:

    HeroName _name;
    std::vector<AbilityName> _abilityNames;
    int _maxHP;
    int _moveAPCost;
    int _remainingRespawnTime;

    friend class InitMessage;
    friend class TurnMessage;

    bool isNull = false;

public:

    static HeroConstants NULL_HERO_CONSTANT;

};


#endif //AIC19_CLIENT_CPP_HEROCONSTANTS_H
