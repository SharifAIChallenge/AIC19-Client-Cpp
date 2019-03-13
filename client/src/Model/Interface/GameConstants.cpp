#include "GameConstants.h"


//----------killScore-------------
int GameConstants::getKillScore() const {
    return _killScore;
}
//-------objectiveZoneScore-------
int GameConstants::getObjectiveZoneScore() const {
    return _objectiveZoneScore;
}
//-----------MaxTurns-------------
int GameConstants::getMaxAP() const {
    return _maxAP;
}
//-----------MaxTurns-------------
int GameConstants::getMaxTurns() const {
    return _maxTurns;
}

int GameConstants::getPreprocessTimeout() const {
    return _preprocessTimeout;
}

int GameConstants::getFirstMoveTimeout() const {
    return _firstMoveTimeout;
}

int GameConstants::getNormalTimeout() const {
    return _normalTimeout;
}

int GameConstants::getMaxScore() const {
    return _maxScore;
}

int GameConstants::getInitOvertime() const {
    return _initOvertime;
}

int GameConstants::getMaxScoreDiff() const {
    return _maxScoreDiff;
}

int GameConstants::getTotalMovePhases() const {
    return _totalMovePhases;
}

