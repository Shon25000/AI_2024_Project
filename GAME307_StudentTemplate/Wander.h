#ifndef  WANDER_H
#define WANDER_H
#include "SteeringBehaviour.h"
#include "Body.h"
#include <random>

class Wander :
    public SteeringBehaviour
{
private:

public:

    Wander(const Body* npc_);



    virtual ~Wander();
    SteeringOutput* getSteering();
};

#endif