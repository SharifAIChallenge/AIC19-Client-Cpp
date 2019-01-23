#ifndef AIC18_CLIENT_CPP_GAMECONSTANTS_H
#define AIC18_CLIENT_CPP_GAMECONSTANTS_H

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

    void set_respawnTime(int respawnTime);
    int get_respawnTime() const;
    int& respawnTime();
    int respawnTime() const;

    void set_timeOut(int timeOut);
    int get_timeOut() const;
    int& timeOut();
    int timeOut() const;

    void set_maxAP(int maxAP);
    int get_maxAP() const;
    int& maxAP();
    int maxAP() const;

    int get_maxTurns() const;
    void set_maxTurns(int maxTurns);
    int& maxTurns();
    int maxTurns() const;

private:
    int _respawnTime;
    int _timeOut;
    int _maxAP;
    int _maxTurns;

};


#endif //AIC18_CLIENT_CPP_GAMECONSTANTS_H
