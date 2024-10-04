#ifndef STEERING_H
#define STEERING_H
#include<MMath.h>

using namespace MATH;  
class Steering
{
public:  
	Vec3 linear;
	float angular;  
  
	Steering();
	Steering(Vec3 linear_, float angular_);

};
#endif
