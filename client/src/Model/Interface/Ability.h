//
// Created by dot_blue on 1/23/19.
//

#ifndef AIC18_CLIENT_CPP_ABILITY_H
#define AIC18_CLIENT_CPP_ABILITY_H

#include "AbilityConstants.h"

class Ability {
public:

    Ability() = default;
    ~Ability() = default;

    Ability(const Ability&) = default;
    Ability& operator=(const Ability&) = default;

    Ability(Ability&&) = default;
    Ability& operator=(Ability&&) = default;

//    Ability(AbilityConstants _abilityConstants);


    void set_abilityConstants(const AbilityConstants &_abilityConstants);
    const AbilityConstants &get_abilityConstants() const;
    AbilityConstants& abilityConstants();
    AbilityConstants abilityConstants() const;

    void set_remCooldown(int _remCooldown);
    int get_remCooldown() const;
    int& remCooldown();
    int remCooldown() const;


private:
    AbilityConstants _abilityConstants;
    int _remCooldown;
};


#endif //AIC18_CLIENT_CPP_ABILITY_H
