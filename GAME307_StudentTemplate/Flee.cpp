#include "Flee.h"

Flee::Flee(const Body* npc_, const Body* target_)
{
	npc = npc_; 
	target = target_; 
}

Flee::~Flee()
{
}

SteeringOutput* Flee::getSteering()
{

	result->linear = npc->getPos() - target->getPos();

	return result;
}
