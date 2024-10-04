#include "KinematicSteering.h"

KinematicSteering::KinematicSteering()
{
	velocity = Vec3(); 
	rotation = 0.0f;

}

KinematicSteering::KinematicSteering(Vec3 velocity_, float rotation_)
{

	velocity = velocity_;
	rotation = rotation_; 

}
