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


    //Getters:
    AbilityName getAbilityName() const;

    AbilityType type() const;

    int range() const;

    int APCost() const;

    int cooldown() const;

    int areaOfEffect() const;

    int power() const;

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


    AbilityName& abilityName();
    AbilityType& type();
    int& range();
    int& APCost();
    int& cooldown();
    int& areaOfEffect();
    int& power();
    bool& isLobbing();
    bool& isPiercing();

    friend class InitMessage;

    bool isNull = false;


public:// TODO single tone
    static AbilityConstants NULL_ABILITY_CONSTANTS;
};


#endif //AIC18_CLIENT_CPP_ABILITYCONSTANTS_H
