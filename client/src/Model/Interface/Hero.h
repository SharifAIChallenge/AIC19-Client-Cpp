#ifndef AIC19_CLIENT_CPP_HERO_H
#define AIC19_CLIENT_CPP_HERO_H


#include "HeroConstants.h"
#include "Ability.h"
#include "Cell.h"

class Hero {
public:

    Hero() = default;
    ~Hero();

    Hero(bool isNull);

    Hero(Hero&);
//    Hero& operator=(const Hero&) = delete;
//
//    Hero(Hero&&) = delete;
//    Hero& operator=(Hero&&) = delete;

//API:
    Ability getAbility(AbilityName _abilityName);
    int getId() const;

    // Updates the other three vectors as well (dodgeAbilities,...)
    std::vector<Ability *> getAbilities() const;
    std::vector<Ability *> getDodgeAbilities() const;
    std::vector<Ability *> getDefensiveAbilities() const;
    std::vector<Ability *> getOffensiveAbilities() const;

    int getCurrentHP() const;
    Cell& getCurrentCell() const;
    std::vector<Cell *> getRecentPath() const;
    int getRemRespawnTime() const;

    // Getters for the heroConstants
    HeroName getName() const;
    std::vector<AbilityName> getAbilityNames() const;
    int getMaxHP() const;
    int getMoveAPCost() const;
    int remainingRespawnTime() const;
    


    // Is it enough to compare the id? answer: Yes (including the isNull's)
    bool operator==(const Hero &_hero);
    bool operator!=(const Hero &_hero);

private:

    int _id;
    int _currentHP;
    int _remRespawnTime;
    HeroConstants _heroConstants;

    std::vector<Ability *> _abilities;
    std::vector<Ability *> _defensiveAbilities;
    std::vector<Ability *> _dodgeAbilities;
    std::vector<Ability *> _offensiveAbilities;

    Cell* _currentCell;
    std::vector<Cell *> _recentPath;//Shouldn't delete these guys in the destructor!


    HeroConstants heroConstants() const;
    void set_abilities(std::vector<Ability *> &_abilities);
    void copy_abilities(std::vector<Ability *> &_abilities);
    void clear_abilities();

    friend class TurnMessage;
    friend class PickMessage;

    bool isNull = false;

public://single tone
    static Hero NULL_HERO;
};


#endif //AIC19_CLIENT_CPP_HERO_H
