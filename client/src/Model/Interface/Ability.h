#ifndef AIC19_CLIENT_CPP_ABILITY_H
#define AIC19_CLIENT_CPP_ABILITY_H


#include "AbilityConstants.h"

class Ability {
public:

    Ability() = default;
    ~Ability() = default;

    Ability(bool isNull);

    Ability(const Ability&) = default;
    Ability& operator=(const Ability&) = default;

    Ability(Ability&&) = default;
    Ability& operator=(Ability&&) = default;
    
//API
//Getters:
    int getRemCooldown() const;
    bool isReady() const;
    
//Getters for the AbilityConstants
    AbilityName getName() const;
    AbilityType getType() const;
    int getRange() const;
    int getAPCost() const;
    int getCooldown() const;
    int getAreaOfEffect() const;
    int getPower() const;
    bool isLobbing() const;

    AbilityConstants getAbilityConstants() const;

    bool operator==(const Ability& _ability);

private:
    AbilityConstants _abilityConstants;
    int _remCooldown;


    friend class TurnMessage;
    friend class PickMessage;

    bool isNull = false;

public://single tone
    static Ability NULL_ABILITY;
};


#endif //AIC19_CLIENT_CPP_ABILITY_H
