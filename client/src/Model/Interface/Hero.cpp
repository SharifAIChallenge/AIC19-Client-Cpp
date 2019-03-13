//
// Created by dot_blue on 1/23/19.
//

#include <iostream>
#include "Hero.h"


Hero::Hero(bool _isNull) {
    if(_isNull) {
//        this->_id = -1;
        this->isNull = true;
    }
}


Hero::~Hero() {// Check the vectors
    for (std::vector<Ability *>::iterator it = _abilities.begin() ; it != _abilities.end(); ++it){
        delete *it;
    }
    _abilities.clear();
}

Hero::Hero(Hero & _hero):_currentCell(_hero._currentCell) {
    this->_id = _hero._id;
    this->_currentHP = _hero._currentHP;
    this->_remRespawnTime = _hero._remRespawnTime;
    this->_heroConstants = _hero._heroConstants;

    this->_recentPath = _hero._recentPath;

    this->copy_abilities(_hero._abilities);
    this->isNull = _hero.isNull;
}

//----------------id-------------------
int Hero::getId() const {
    return _id;
}
//------------currentHP----------------
int Hero::getCurrentHP() const {
    return _currentHP;
}
//------------respawnTime--------------
int Hero::getRemRespawnTime() const {
    return _remRespawnTime;
}
//-----------heroConstants-------------
HeroConstants Hero::heroConstants() const {
    return _heroConstants;
}
//-------------abilities---------------
std::vector<Ability *> Hero::getAbilities() const {
    return _abilities;
}

void Hero::set_abilities(std::vector<Ability *> &input_abilities) {
    this->clear_abilities();

    for(Ability* _abil:input_abilities) {
        Ability* tmp_abil = new Ability(*_abil);
        this->_abilities.push_back(tmp_abil);
    }

    for(std::vector<Ability *>::iterator it = this->_abilities.begin();
        it < this->_abilities.end(); ++it){
        if((*it)->getType() == AbilityType::OFFENSIVE){
            _offensiveAbilities.push_back(*it);
        } else if ((*it)->getType() == AbilityType::DODGE){
            _dodgeAbilities.push_back(*it);
        } else if ((*it)->getType() == AbilityType::DEFENSIVE){
            _defensiveAbilities.push_back(*it);
        }
    }
}

void Hero::copy_abilities(std::vector<Ability *> &_abilities) {
    this->clear_abilities();
    for(Ability * ability_ptr : _abilities){
        Ability* tmp_ability_ptr = new Ability(*ability_ptr);
        this->_abilities.push_back(tmp_ability_ptr);
    }

    for(std::vector<Ability *>::iterator it = this->_abilities.begin();
        it < this->_abilities.end(); ++it){
        if((*it)->getType() == AbilityType::OFFENSIVE){
            _offensiveAbilities.push_back(*it);
        } else if ((*it)->getType() == AbilityType::DODGE){
            _dodgeAbilities.push_back(*it);
        } else if ((*it)->getType() == AbilityType::DEFENSIVE){
            _defensiveAbilities.push_back(*it);
        }
    }
}

std::vector<Ability *> Hero::getDodgeAbilities() const {
    return _dodgeAbilities;
}

std::vector<Ability *> Hero::getDefensiveAbilities() const {
    return _defensiveAbilities;
}

std::vector<Ability *> Hero::getOffensiveAbilities() const {
    return _offensiveAbilities;
}
//-------------currentCell---------------
Cell& Hero::getCurrentCell() const {
    return *_currentCell;
}
//-------------recentPath----------------
std::vector<Cell *> Hero::getRecentPath() const {
    return _recentPath;
}

bool Hero::operator==(const Hero &_hero) {
    return (this->_id == _hero.getId()) && (this->isNull == _hero.isNull);
}

bool Hero::operator!=(const Hero &_hero) {
    return !(*this == _hero);
}


HeroName Hero::getName() const {
    return _heroConstants.getName();
}

std::vector<AbilityName> Hero::getAbilityNames() const {
    return _heroConstants.getAbilityNames();
}

int Hero::getMaxHP() const {
    return _heroConstants.getMaxHP();
}

int Hero::getMoveAPCost() const {
    return _heroConstants.getMoveAPCost();
}

int Hero::remainingRespawnTime() const {
    return _heroConstants.getRespawnTime();
}

Ability Hero::getAbility(AbilityName _abilityName) {
    for(Ability * tmp_ability : this->_abilities){
        if(tmp_ability->getName() == _abilityName)
            return *tmp_ability;
    }

    return Ability::NULL_ABILITY;
}

void Hero::clear_abilities() {
    for (std::vector<Ability *>::iterator it = this->_abilities.begin() ; it != this->_abilities.end(); ++it){
        delete *it;
    }
    this->_abilities.clear();
    this->_offensiveAbilities.clear();
    this->_dodgeAbilities.clear();
    this->_defensiveAbilities.clear();
}


//Single tone
Hero Hero::NULL_HERO(true);






