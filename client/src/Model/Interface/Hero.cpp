//
// Created by dot_blue on 1/23/19.
//

#include "Hero.h"


Hero::Hero(bool _isNull):Hero(),isNull(_isNull) {}


Hero::~Hero() {//TODO Check the vectors
    for (std::vector<Ability *>::iterator it = _abilities.begin() ; it != _abilities.end(); ++it){
        delete *it;
    }
    _abilities.clear();

    for (std::vector<Ability *>::iterator it = _dodgeAbilities.begin() ; it != _dodgeAbilities.end(); ++it){
        delete *it;
    }
    _dodgeAbilities.clear();

    for (std::vector<Ability *>::iterator it = _healAbilities.begin() ; it != _healAbilities.end(); ++it){
        delete *it;
    }
    _healAbilities.clear();

    for (std::vector<Ability *>::iterator it = _attackAbilities.begin() ; it != _attackAbilities.end(); ++it){
        delete *it;
    }
    _attackAbilities.clear();
}
//----------------id-------------------
void Hero::set_id(int _id) {
    Hero::_id = _id;
}

int Hero::get_id() const {
    return _id;
}

int &Hero::id() {
    return _id;
}

int Hero::id() const {
    return _id;
}
//------------currentHP----------------
int Hero::get_currentHP() const {
    return _currentHP;
}

void Hero::set_currentHP(int _currentHP) {
    Hero::_currentHP = _currentHP;
}

int &Hero::currentHP() {
    return _currentHP;
}

int Hero::currentHP() const {
    return _currentHP;
}
//-----------heroConstants-------------
const HeroConstants &Hero::get_heroConstants() const {
    return _heroConstants;
}

void Hero::set_heroConstants(const HeroConstants &_heroConstants) {
    Hero::_heroConstants = _heroConstants;
}

HeroConstants &Hero::heroConstants() {
    return _heroConstants;
}

HeroConstants Hero::heroConstants() const {
    return _heroConstants;
}
//-------------abilities---------------
const std::vector<Ability *> &Hero::get_abilities() const {
    return _abilities;
}

void Hero::set_abilities(const std::vector<Ability *> &_abilities) {
    Hero::_abilities = _abilities;
}

const std::vector<Ability *> &Hero::get_dodgeAbilities() const {
    return _dodgeAbilities;
}

void Hero::set_dodgeAbilities(const std::vector<Ability *> &_dodgeAbilities) {
    Hero::_dodgeAbilities = _dodgeAbilities;
}

const std::vector<Ability *> &Hero::get_healAbilities() const {
    return _healAbilities;
}

void Hero::set_healAbilities(const std::vector<Ability *> &_healAbilities) {
    Hero::_healAbilities = _healAbilities;
}

const std::vector<Ability *> &Hero::get_attackAbilities() const {
    return _attackAbilities;
}

void Hero::set_attackAbilities(const std::vector<Ability *> &_attackAbilities) {
    Hero::_attackAbilities = _attackAbilities;
}
//-------------currentCell---------------
const Cell &Hero::get_currentCell() const {
    return _currentCell;
}

void Hero::set_currentCell(const Cell &_currentCell) {
    Hero::_currentCell = _currentCell;
}

Cell &Hero::currentCell() {
    return _currentCell;
}

Cell Hero::currentCell() const {
    return _currentCell;
}
//-------------recentPath----------------
const std::vector<Cell *> &Hero::get_recentPath() const {
    return _recentPath;
}

void Hero::set_recentPath(const std::vector<Cell *> &_recentPath) {
    Hero::_recentPath = _recentPath;
}

bool Hero::operator==(Hero _hero) {
    return (this->_id == _hero.id()) && (this->isNull == _hero.isNull);
}

bool Hero::operator!=(Hero _hero) {
    return !(*this == _hero);
}

//Single tone
Hero Hero::NULL_HERO(true);



