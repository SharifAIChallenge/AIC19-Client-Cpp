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

    void set_RespawnTime(int respawnTime);
    int get_RespawnTime() const;
    int& RespawnTime();
    int RespawnTime() const;

    void set_TimeOut(int timeOut);
    int get_TimeOut() const;
    int& TimeOut();
    int TimeOut() const;

    void set_MaxAP(int maxAP);
    int get_MaxAP() const;
    int& MaxAP();
    int MaxAP() const;

    int get_MaxTurns() const;
    void set_MaxTurns(int maxTurns);
    int& MaxTurns();
    int MaxTurns() const;

private:
    int respawnTime;
    int timeOut;
    int maxAP;
    int maxTurns;

};


#endif //AIC18_CLIENT_CPP_GAMECONSTANTS_H
