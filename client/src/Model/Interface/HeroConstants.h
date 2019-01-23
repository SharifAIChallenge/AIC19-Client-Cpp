#ifndef AIC18_CLIENT_CPP_HEROCONSTANTS_H
#define AIC18_CLIENT_CPP_HEROCONSTANTS_H

#include "Enumerations.h"
#include <vector>

class HeroConstants {
public:
    HeroConstants() = default;
    ~HeroConstants();

    HeroConstants(const HeroConstants&) = default;
    HeroConstants& operator=(const HeroConstants&) = default;

    void set_name(HeroName name);
    HeroName get_name() const;
    HeroName& name();
    HeroName name() const;

    void set_abilityNames(const std::vector<AbilityName *> &abilityName);
    const std::vector<AbilityName *> &get_abilityNames() const;


    void set_maxHP(int maxHP);
    int get_maxHP() const;
    int& maxHP();
    int maxHP() const;


    void set_moveAPCost(int moveAPCost);
    int get_moveAPCost() const;
    int& moveAPCost();
    int moveAPCost() const;


private:
    HeroName _name;

    std::vector<AbilityName *> _abilityNames;

    int _maxHP;

    int _moveAPCost;

};


#endif //AIC18_CLIENT_CPP_HEROCONSTANTS_H
