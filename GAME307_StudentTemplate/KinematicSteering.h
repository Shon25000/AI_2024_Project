#ifndef KINEMATICSTEERING_H
#define KINEMATICSTEERING_H
#include<Vector.h> 
using namespace MATH; 
class KinematicSteering
{
public:
	Vec3 velocity;
	float rotation;

	KinematicSteering();
	KinematicSteering(Vec3 velocity_, float rotation_);
};

#endif // !KINEMATICSTEERING_H