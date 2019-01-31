#ifndef AIC18_CLIENT_CPP_AI_H
#define AIC18_CLIENT_CPP_AI_H

//#include <Model/World.h>
#include <Model/Interface/Game.h>
class World;

class AI {
public:

    void simple_turn(World* world);

    void complex_turn(World* world);

};

#endif // AIC18_CLIENT_CPP_AI_H
