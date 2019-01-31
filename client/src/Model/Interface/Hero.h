//
// Created by dot_blue on 1/23/19.
//

#ifndef AIC18_CLIENT_CPP_HERO_H
#define AIC18_CLIENT_CPP_HERO_H


#include "HeroConstants.h"
#include "Ability.h"
#include "Cell.h"

class Hero {
public:

    Hero() = default;
    ~Hero();

    Hero(bool isNull);

    Hero(const Hero&) = default;
    Hero& operator=(const Hero&) = default;

    Hero(Hero&&) = default;
    Hero& operator=(Hero&&) = default;

    int id() const;
    int currentHP() const;
    int respawnTime() const;

    // TODO put getters for the heroConstants
    HeroName name() const;
    const std::vector<AbilityName> &abilityNames() const;
    int maxHP() const;
    int moveAPCost() const;
    int remainingRespawnTime() const;

    //TODO you have to update the other three vectors as well (dodgeAbilities,...)
    void set_abilities(const std::vector<Ability *> &_abilities);
    const std::vector<Ability *> &get_abilities() const;

    //TODO We shouldn't need these functions (set_abilities() will do it?)
    const std::vector<Ability *> &get_dodgeAbilities() const;
    const std::vector<Ability *> &get_healAbilities() const;
    const std::vector<Ability *> &get_attackAbilities() const;


    Cell& currentCell();
    Cell currentCell() const;


    void set_recentPath(const std::vector<Cell *> &_recentPath);
    const std::vector<Cell *> &get_recentPath() const;

    //TODO: is it enough to compare the id?
    bool operator==(Hero _hero);
    bool operator!=(Hero _hero);

private:

    int _id;
    int _currentHP;
    int _respawnTime;
    HeroConstants _heroConstants;

    std::vector<Ability *> _abilities;
    std::vector<Ability *> _dodgeAbilities;
    std::vector<Ability *> _healAbilities;
    std::vector<Ability *> _attackAbilities;

    Cell _currentCell;
    std::vector<Cell *> _recentPath;


    HeroConstants& heroConstants();
    HeroConstants heroConstants() const;

    int& id();
    int& currentHP();
    int& respawnTime();

    friend class TurnMessage;
    friend class PickMessage;

    bool isNull = false;

public://single tone
    static Hero NULL_HERO;
};


#endif //AIC18_CLIENT_CPP_HERO_H
