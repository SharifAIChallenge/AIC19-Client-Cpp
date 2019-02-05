//
// Created by dot_blue on 1/23/19.
//

#include "Hero.h"


Hero::Hero(bool _isNull):isNull(_isNull) {}


Hero::~Hero() {// Check the vectors
    for (std::vector<Ability *>::iterator it = _abilities.begin() ; it != _abilities.end(); ++it){
        delete *it;
    }
    _abilities.clear();
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

void Hero::set_abilities(std::vector<Ability *> &_abilities) {
    Hero::_abilities = _abilities;

    for(std::vector<Ability *>::iterator it = _abilities.begin();
            it < _abilities.end(); ++it){
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
Cell Hero::getCurrentCell() const {
    return _currentCell;
}
//-------------recentPath----------------
std::vector<Cell *> Hero::getRecentPath() const {
    return _recentPath;
}

bool Hero::operator==(Hero _hero) {
    return (this->_id == _hero.getId()) && (this->isNull == _hero.isNull);
}

bool Hero::operator!=(Hero _hero) {
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



//Single tone
Hero Hero::NULL_HERO(true);




