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

    void set_Name(HeroName name);
    HeroName get_Name() const;
    HeroName& Name();
    HeroName Name() const;

    void set_AbilityNames(const std::vector<AbilityName *> &AbilityName);
    const std::vector<AbilityName *> &get_AbilityNames() const;


    void set_MaxHP(int maxHP);
    int get_MaxHP() const;
    int& MaxHP();
    int MaxHP() const;


    void set_MoveAPCost(int moveAPCost);
    int get_MoveAPCost() const;
    int& MoveAPCost();
    int MoveAPCost() const;


private:
    HeroName name;

    std::vector<AbilityName *> AbilityNames;

    int maxHP;

    int moveAPCost;

};


#endif //AIC18_CLIENT_CPP_HEROCONSTANTS_H
