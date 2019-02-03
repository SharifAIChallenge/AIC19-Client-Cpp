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

    HeroName& name();
    HeroName name() const;

    void set_abilityNames(std::vector<AbilityName> abilityName);
    const std::vector<AbilityName> &get_abilityNames() const;


    int& maxHP();
    int maxHP() const;


    int& moveAPCost();
    int moveAPCost() const;

    int& remainingRespawnTime();
    int remainingRespawnTime() const;

private:

    HeroName _name;

    std::vector<AbilityName> _abilityNames;

    int _maxHP;

    int _moveAPCost;

    int _remainingRespawnTime;


    bool isNull = false;

public:

    static HeroConstants NULL_HERO_CONSTANT;

};


#endif //AIC19_CLIENT_CPP_HEROCONSTANTS_H
