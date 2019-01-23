//
// Created by dot_blue on 1/23/19.
//

#ifndef AIC18_CLIENT_CPP_HERO_H
#define AIC18_CLIENT_CPP_HERO_H


#include "HeroConstants.h"
#include "Ability.h"

//TODO these guys need to be implemented:
class DodgeAbility;
class PowerAbility;
class Cell;

class Hero {
public:

    Hero() = default;
    ~Hero();

    Hero(const Hero&) = default;
    Hero& operator=(const Hero&) = default;

    Hero(Hero&&) = default;
    Hero& operator=(Hero&&) = default;

    void set_id(int _id);
    int get_id() const;
    int& id();
    int id() const;

    void set_currentHP(int _currentHP);
    int get_currentHP() const;
    int& currentHP();
    int currentHP() const;


    void set_heroConstants(const HeroConstants &_heroConstants);
    const HeroConstants &get_heroConstants() const;
    HeroConstants& heroConstants();
    HeroConstants heroConstants() const;


    void set_abilities(const std::vector<Ability *> &_abilities);
    const std::vector<Ability *> &get_abilities() const;


    void set_dodgeAbilities(const std::vector<DodgeAbility *> &_dodgeAbilities);
    const std::vector<DodgeAbility *> &get_dodgeAbilities() const;


    void set_healAbilities(const std::vector<PowerAbility *> &_healAbilities);
    const std::vector<PowerAbility *> &get_healAbilities() const;


    void set_attackAbilities(const std::vector<PowerAbility *> &_attackAbilities);
    const std::vector<PowerAbility *> &get_attackAbilities() const;


    void set_currentCell(const Cell &_currentCell);
    const Cell &get_currentCell() const;
    Cell& currentCell();
    Cell currentCell() const;


    void set_recentPath(const std::vector<Cell *> &_recentPath);
    const std::vector<Cell *> &get_recentPath() const;



private:

    int _id;
    int _currentHP;
    HeroConstants _heroConstants;

    std::vector<Ability *> _abilities;
    std::vector<DodgeAbility *> _dodgeAbilities;
    std::vector<PowerAbility *> _healAbilities;
    std::vector<PowerAbility *> _attackAbilities;

    Cell _currentCell;
    std::vector<Cell *> _recentPath;

};


#endif //AIC18_CLIENT_CPP_HERO_H
