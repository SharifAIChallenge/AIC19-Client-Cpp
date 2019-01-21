#include "GameConstants.h"


GameConstants::~GameConstants() {

}
//-----------RespawnTime-----------
int GameConstants::get_RespawnTime() const {
    return respawnTime;
}

void GameConstants::set_RespawnTime(int respawnTime) {
    GameConstants::respawnTime = respawnTime;
}

int& GameConstants::RespawnTime() {
    return respawnTime;
}

int GameConstants::RespawnTime() const {
    return respawnTime;
}
//------------TimeOut-------------
void GameConstants::set_TimeOut(int timeOut) {
    GameConstants::timeOut = timeOut;
}

int GameConstants::get_TimeOut() const {
    return timeOut;
}

int& GameConstants::TimeOut() {
    return timeOut;
}

int GameConstants::TimeOut() const {
    return timeOut;
}
//-------------MaxAP--------------
int GameConstants::get_MaxAP() const {
    return maxAP;
}

void GameConstants::set_MaxAP(int maxAP) {
    GameConstants::maxAP = maxAP;
}

int& GameConstants::MaxAP() {
    return maxAP;
}

int GameConstants::MaxAP() const {
    return maxAP;
}
//-----------MaxTurns-------------
int GameConstants::get_MaxTurns() const {
    return maxTurns;
}

void GameConstants::set_MaxTurns(int maxTurns) {
    GameConstants::maxTurns = maxTurns;
}

int& GameConstants::MaxTurns() {
    return maxTurns;
}

int GameConstants::MaxTurns() const {
    return maxTurns;
}

