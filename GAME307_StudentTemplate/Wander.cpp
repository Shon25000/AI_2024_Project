#include "Wander.h"

Wander::Wander(const Body* npc_)
{
	npc = npc_;
}

Wander::~Wander()
{
}

SteeringOutput* Wander::getSteering()
{
	//private Vector3 OrientationToVector(float orientation)
	// {  
	//	return new Vector3(Mathf.Cos(orientation), 0,  Mathf.Sin(orientation));  
	// }



	//result->linear = npc->getMaxSpeed() *  npc->getOrientation(); // Orientation as a vector

	// private float RandomBinomial(){  
	// return Random.value - Random.value;  
	// }

	// result->angular = npc->getPos(rand()) * npc->getMaxRotation();

	return result;

}
