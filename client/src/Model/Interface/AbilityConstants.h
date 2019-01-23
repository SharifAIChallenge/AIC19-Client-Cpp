#ifndef AIC18_CLIENT_CPP_ABILITYCONSTANTS_H
#define AIC18_CLIENT_CPP_ABILITYCONSTANTS_H

#include "Enumerations.h"
#include <string>

class AbilityConstants {
public:
    AbilityConstants() = default;
    ~AbilityConstants() = default;

    AbilityConstants(const AbilityConstants&) = default;
    AbilityConstants& operator=(const AbilityConstants&) = default;

    AbilityConstants(AbilityConstants&&) = default;
    AbilityConstants& operator=(AbilityConstants&&) = default;


    void set_abilityName(AbilityName _abilityName);
    AbilityName get_abilityName() const;
    AbilityName& abilityName();
    AbilityName abilityName() const;

    void set_type(const std::string &_type);
    const std::string &get_type() const;
    std::string& type();
    std::string type() const;

    void set_range(int _range);
    int get_range() const;
    int& range();
    int range() const;

    void set_APCost(int _APCost);
    int get_APCost() const;
    int& APCost();
    int APCost() const;

    void set_cooldown(int _cooldown);
    int get_cooldown() const;
    int& cooldown();
    int cooldown() const;

    void set_areaOfEffect(int _areaOfEffect);
    int get_areaOfEffect() const;
    int& areaOfEffect();
    int areaOfEffect() const;

    void set_power(int _power);
    int get_power() const;
    int& power();
    int power() const;

    void set_Lobbing(bool _isLobbing);
    bool is_Lobbing() const;
    bool& isLobbing();
    bool isLobbing() const;


    void set_Piercing(bool _isPiercing);
    bool is_Piercing() const;
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
};


#endif //AIC18_CLIENT_CPP_ABILITYCONSTANTS_H
