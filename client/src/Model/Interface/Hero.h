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
    int getCurrentHP() const;
    int respawnTime() const;

    // Getters for the heroConstants
    HeroName name() const;
    const std::vector<AbilityName> &abilityNames() const;
    int maxHP() const;
    int moveAPCost() const;
    int remainingRespawnTime() const;

    // Updates the other three vectors as well (dodgeAbilities,...)
    void set_abilities(std::vector<Ability *> &_abilities);
    const std::vector<Ability *> &get_abilities() const;

    const std::vector<Ability *> &get_dodgeAbilities() const;
    const std::vector<Ability *> &get_healAbilities() const;
    const std::vector<Ability *> &get_attackAbilities() const;


    Cell& currentCell();
    Cell currentCell() const;


    void set_recentPath(const std::vector<Cell *> &_recentPath);
    const std::vector<Cell *> &get_recentPath() const;

    // Is it enough to compare the id? answer: Yes (including the isNull's)
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
    std::vector<Cell *> _recentPath;//Shouldn't delete these guys in the constructor!


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
