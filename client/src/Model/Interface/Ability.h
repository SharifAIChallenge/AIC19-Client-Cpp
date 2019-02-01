#ifndef AIC19_CLIENT_CPP_ABILITY_H
#define AIC19_CLIENT_CPP_ABILITY_H


#include "AbilityConstants.h"

class Ability {
public:

    Ability() = default;
    ~Ability() = default;

    Ability(const Ability&) = default;
    Ability& operator=(const Ability&) = default;

    Ability(Ability&&) = default;
    Ability& operator=(Ability&&) = default;

//Getters for the AbilityConstants
    AbilityName abilityName() const;
    AbilityType type() const;
    int range() const;
    int APCost() const;
    int cooldown() const;
    int areaOfEffect() const;
    int power() const;
    bool isLobbing() const;
    bool isPiercing() const;

//Getters:
    int remCooldown() const;
    AbilityConstants getAbilityConstants() const;


private:
    AbilityConstants _abilityConstants;
    int _remCooldown;


    AbilityConstants& abilityConstants();

    int& remCooldown();

    friend class TurnMessage;
    friend class PickMessage;

};


#endif //AIC19_CLIENT_CPP_ABILITY_H
