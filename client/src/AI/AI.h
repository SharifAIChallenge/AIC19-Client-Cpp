#ifndef AIC19_CLIENT_CPP_AI_H
#define AIC19_CLIENT_CPP_AI_H

#include <Model/Interface/World.h>

class AI {
public:
    void preProcess(World* world);

    void pick(World* world);

    void move(World* world);

    void action(World* world);

};

#endif // AIC19_CLIENT_CPP_AI_H
