#include "Wander.h"

Wander::Wander(const Body* npc_)
{
	npc = npc_;
}

Wander::~Wander()
{
}



float randomBinomial()
{
	// float RandomBinomial(){  
	// return Random.value - Random.value;  
	// }

	return ((double)rand() / RAND_MAX) - ((double)rand() / RAND_MAX);
}


SteeringOutput* Wander::getSteering()
{
	// Orientation as a vector is (X) cos(Orientation), (Y) Sin(Orientation), (Z) 0

	result->linear = npc->getMaxAcceleration() * Vec3(cos(npc->getOrientation()), sin(npc->getOrientation()), 0);

	 result->angular = randomBinomial() * npc->getMaxRotation();

	return result;

}
