#ifndef AIC18_CLIENT_CPP_AI_H
#define AIC18_CLIENT_CPP_AI_H

//#include <Model/World.h>
#include <Model/Interface/World.h>

class AI {
public:
    void preProcess(World* world);

    void pick(World* world);

    void move(World* world);

    void action(World* world);

};

#endif // AIC18_CLIENT_CPP_AI_H
