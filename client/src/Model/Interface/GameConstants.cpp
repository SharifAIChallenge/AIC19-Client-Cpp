#include "GameConstants.h"


GameConstants::~GameConstants() {

}
//-----------RespawnTime-----------
int GameConstants::get_respawnTime() const {
    return _respawnTime;
}

void GameConstants::set_respawnTime(int respawnTime) {
    GameConstants::_respawnTime = respawnTime;
}

int& GameConstants::respawnTime() {
    return _respawnTime;
}

int GameConstants::respawnTime() const {
    return _respawnTime;
}
//------------TimeOut-------------
void GameConstants::set_timeOut(int timeOut) {
    GameConstants::_timeOut = timeOut;
}

int GameConstants::get_timeOut() const {
    return _timeOut;
}

int& GameConstants::timeOut() {
    return _timeOut;
}

int GameConstants::timeOut() const {
    return _timeOut;
}
//-------------MaxAP--------------
int GameConstants::get_maxAP() const {
    return _maxAP;
}

void GameConstants::set_maxAP(int maxAP) {
    GameConstants::_maxAP = maxAP;
}

int& GameConstants::maxAP() {
    return _maxAP;
}

int GameConstants::maxAP() const {
    return _maxAP;
}
//-----------MaxTurns-------------
int GameConstants::get_maxTurns() const {
    return _maxTurns;
}

void GameConstants::set_maxTurns(int maxTurns) {
    GameConstants::_maxTurns = maxTurns;
}

int& GameConstants::maxTurns() {
    return _maxTurns;
}

int GameConstants::maxTurns() const {
    return _maxTurns;
}

