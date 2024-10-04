#include "Steering.h"

Steering::Steering()
{
	linear = Vec3(0.0f,0.0f,0.0f); 
	angular = 0.0f;
}

Steering::Steering(Vec3 linear_, float angular_)
{
	linear = linear_;
	angular = angular_;

}
