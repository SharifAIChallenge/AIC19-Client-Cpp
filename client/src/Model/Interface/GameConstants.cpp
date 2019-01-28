#include "GameConstants.h"


GameConstants::~GameConstants() {

}
//----------killScore-------------
int &GameConstants::killScore() {
    return _killScore;
}

int GameConstants::killScore() const {
    return _killScore;
}
//-------objectiveZoneScore-------
int &GameConstants::objectiveZoneScore() {
    return _objectiveZoneScore;
}

int GameConstants::objectiveZoneScore() const {
    return _objectiveZoneScore;
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

