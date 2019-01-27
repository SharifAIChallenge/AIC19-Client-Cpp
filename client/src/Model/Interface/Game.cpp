//
// Created by dot_blue on 1/23/19.
//

#include "Game.h"
//----------------map------------------
const Map &Game::get_map() const {
    return _map;
}

void Game::set_map(const Map &_map) {
    Game::_map = _map;
}

Map &Game::map() {
    return _map;
}
//------------gameConstants------------
const GameConstants &Game::get_gameConstants() const {
    return _gameConstants;
}

void Game::set_gameConstants(const GameConstants &_gameConstants) {
    Game::_gameConstants = _gameConstants;
}

GameConstants &Game::gameConstants() {
    return _gameConstants;
}
//------------abilityConstants---------
const AbilityConstants &Game::get_abilityConstants() const {
    return _abilityConstants;
}

void Game::set_abilityConstants(const AbilityConstants &_abilityConstants) {
    Game::_abilityConstants = _abilityConstants;
}

AbilityConstants &Game::abilityConstants() {
    return _abilityConstants;
}
//--------------heroConstants----------
const HeroConstants &Game::get_heroConstants() const {
    return _heroConstants;
}

void Game::set_heroConstants(const HeroConstants &_heroConstants) {
    Game::_heroConstants = _heroConstants;
}

HeroConstants &Game::heroConstants() {
    return _heroConstants;
}
//-----------------AP------------------
int Game::get_AP() const {
    return _AP;
}

void Game::set_AP(int _AP) {
    Game::_AP = _AP;
}

int &Game::AP() {
    return _AP;
}
//----------------score----------------
int Game::get_score() const {
    return _score;
}

void Game::set_score(int _score) {
    Game::_score = _score;
}

int &Game::score() {
    return _score;
}

Game::~Game() {
    for (std::vector<Hero *>::iterator it = _myHeroes.begin() ; it != _myHeroes.end(); ++it){
        delete *it;
    }
    _myHeroes.clear();

    for (std::vector<Hero *>::iterator it = _oppHeroes.begin() ; it != _oppHeroes.end(); ++it){
        delete *it;
    }
    _oppHeroes.clear();

    for (std::vector<Hero *>::iterator it = _myDeadHeroes.begin() ; it != _myDeadHeroes.end(); ++it){
        delete *it;
    }
    _myDeadHeroes.clear();

    for (std::vector<Cell *>::iterator it = _brokenWalls.begin() ; it != _brokenWalls.end(); ++it){
        delete *it;
    }
    _brokenWalls.clear();

    for (std::vector<Cell *>::iterator it = _createdWalls.begin() ; it != _createdWalls.end(); ++it){
        delete *it;
    }
    _createdWalls.clear();

}
//logical functions:
Hero Game::getHero(int id) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it){
        if((*it)->get_id() == id){
            return **it;
        }
    }
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it != _oppHeroes.end(); ++it){
        if((*it)->get_id() == id){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero Game::getMyHero(Cell cell) {
    for(std::vector<Hero *>::iterator it = _myHeroes.begin(); it != _myHeroes.end(); ++it ){
        //This only checks the location of the cell
        if((*it)->get_currentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}

Hero Game::getOppHero(Cell cell) {
    for(std::vector<Hero *>::iterator it = _oppHeroes.begin(); it!= _oppHeroes.end(); ++it){
        //This only checks the location of the cell
        if((*it)->get_currentCell() == cell){
            return **it;
        }
    }
    return Hero::NULL_HERO;
}




