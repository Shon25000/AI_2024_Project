#ifndef ARRIVE_H
#define ARRIVE_H
#include"SteeringBehaviour.h"
#include"Body.h" 
class Arrive : public SteeringBehaviour
{

protected: 
	const Body* target;

	float timeToTarget;

public:

	Arrive(const Body* npc_, const Body* target_);  
	SteeringOutput* getSteering();



};

#endif // !ARRIVE_H