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


    void set_dodgeAbilities(const std::vector<Ability *> &_dodgeAbilities);
    const std::vector<Ability *> &get_dodgeAbilities() const;


    void set_healAbilities(const std::vector<Ability *> &_healAbilities);
    const std::vector<Ability *> &get_healAbilities() const;


    void set_attackAbilities(const std::vector<Ability *> &_attackAbilities);
    const std::vector<Ability *> &get_attackAbilities() const;


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
    std::vector<Ability *> _dodgeAbilities;
    std::vector<Ability *> _healAbilities;
    std::vector<Ability *> _attackAbilities;

    Cell _currentCell;
    std::vector<Cell *> _recentPath;


public://single tone
    static Hero NULL_HERO;
};


#endif //AIC18_CLIENT_CPP_HERO_H
