#include "Kinematic.h"

void Kinematic::Update(Steering* steering, float deltaTime) 
{
	pos += velocity * deltaTime;  
	orentation += rotation * deltaTime; 

	velocity += steering->linear * deltaTime; 
	rotation += steering->angular * deltaTime;

	if (VMath::mag(velocity) > maxSpeed) {
		velocity = VMath::normalize(velocity);  
		velocity *= maxSpeed; 
	}
}
