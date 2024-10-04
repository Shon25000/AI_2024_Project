#ifndef KINEMATIX_H
#define KINEMATIX_H

#include"Steering.h"
#include<iostream>
#include<VMath.h>
#include<MMath.h> 
using namespace MATH;  
class Kinematic
{
public: 
	Vec3 pos; 
	Vec3 velocity; 
	float rotation;  
	float orentation;   
	float maxSpeed;

	void Update(Steering* steering, float deltaTime); 

};

#endif 

