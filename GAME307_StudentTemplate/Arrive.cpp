#include "Arrive.h"

Arrive::Arrive(const Body* npc_, const Body* target_)
{

    npc = npc_; 
    target = target_;

    timeToTarget = 5.0f;
}

SteeringOutput* Arrive::getSteering()
{
    SteeringOutput* result = new SteeringOutput();

    result->linear = target->getPos() - npc->getPos();
     
    if (VMath::mag(result->linear) < npc->getRotation()) {  
        
        return nullptr;
    }
    result->linear /= timeToTarget;
    
    if (VMath::mag(result->linear) > npc->getMaxSpeed()) { 
        result->linear = VMath::normalize(result->linear) * npc->getMaxSpeed(); 
    } 
    
     MMath::rotate(npc->getOrientation(), result->linear);
    
    result->angular = 0.0f;

    return result; 
}
