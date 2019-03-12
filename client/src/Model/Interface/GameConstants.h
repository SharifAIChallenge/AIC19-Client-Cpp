#ifndef AIC19_CLIENT_CPP_GAMECONSTANTS_H
#define AIC19_CLIENT_CPP_GAMECONSTANTS_H

//GameConstants
//{
//      respawnTime: int
//      timeout: int
//      maxAP: int
//      maxTurns: int
//}

class GameConstants final{
public:

    GameConstants() = default;
    ~GameConstants() = default;

    GameConstants(const GameConstants&) = default;
    GameConstants& operator=(const GameConstants&) = default;

    GameConstants(GameConstants&&) = default;
    GameConstants& operator=(GameConstants&&) = default;

//API:
    int getKillScore() const;
    int getObjectiveZoneScore() const;
    int getMaxAP() const;
    int getMaxTurns() const;
    int getPreprocessTimeout() const;
    int getFirstMoveTimeout() const;
    int getNormalTimeout() const;
    int getMaxScore() const;
    int getInitOvertime() const;
    int getMaxScoreDiff() const;
    int getTotalMovePhases() const;

private:
    int _killScore;
    int _objectiveZoneScore;
    int _maxAP;
    int _maxTurns;
    int _preprocessTimeout;
    int _firstMoveTimeout;
    int _normalTimeout;
    int _maxScore;
    int _initOvertime;
    int _maxScoreDiff;
    int _totalMovePhases;
    
    friend class InitMessage;
    
};


#endif //AIC19_CLIENT_CPP_GAMECONSTANTS_H
