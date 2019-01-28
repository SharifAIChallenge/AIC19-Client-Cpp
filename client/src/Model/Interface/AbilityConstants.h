#ifndef AIC18_CLIENT_CPP_ABILITYCONSTANTS_H
#define AIC18_CLIENT_CPP_ABILITYCONSTANTS_H

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


    AbilityName& abilityName();
    AbilityName abilityName() const;

    std::string& type();
    std::string type() const;

    int& range();
    int range() const;

    int& APCost();
    int APCost() const;

    int& cooldown();
    int cooldown() const;

    int& areaOfEffect();
    int areaOfEffect() const;

    int& power();
    int power() const;

    bool& isLobbing();
    bool isLobbing() const;


    bool& isPiercing();
    bool isPiercing() const;


private:
    AbilityName _abilityName;
    std::string _type;

    int _range;
    int _APCost;
    int _cooldown;

    int _areaOfEffect;
    int _power;
    bool _isLobbing;
    bool _isPiercing;

    bool isNull = false;

public:// TODO single tone
    static AbilityConstants NULL_ABILITY_CONSTANTS;
};


#endif //AIC18_CLIENT_CPP_ABILITYCONSTANTS_H
