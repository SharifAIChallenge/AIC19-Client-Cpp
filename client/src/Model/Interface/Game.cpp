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
