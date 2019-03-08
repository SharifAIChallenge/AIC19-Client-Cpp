#ifndef AIC19_CLIENT_CPP_ABILITYCONSTANTS_H
#define AIC19_CLIENT_CPP_ABILITYCONSTANTS_H

#include "Enumerations.h"
#include <string>

class AbilityConstants {
public:
    AbilityConstants() = default;
    ~AbilityConstants() = default;

    AbilityConstants(bool _isNull);

    AbilityConstants(const AbilityConstants&) = default;
    AbilityConstants& operator=(const AbilityConstants&) = default;

    AbilityConstants(AbilityConstants&&) = default;
    AbilityConstants& operator=(AbilityConstants&&) = default;

    bool operator==(const AbilityConstants&);

    //API:
    AbilityName getName() const;
    AbilityType getType() const;
    int getRange() const;
    int getAPCost() const;
    int getCooldown() const;
    int getAreaOfEffect() const;
    int getPower() const;
    bool isLobbing() const;
    bool isPiercing() const;

private:
    AbilityName _abilityName;
    AbilityType _type;

    int _range;
    int _APCost;
    int _cooldown;
    int _areaOfEffect;
    int _power;
    bool _isLobbing;
    bool _isPiercing;


    friend class InitMessage;

    bool isNull = false;

public:// single tone
    static AbilityConstants NULL_ABILITY_CONSTANTS;
};


#endif //AIC19_CLIENT_CPP_ABILITYCONSTANTS_H
