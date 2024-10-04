#include "AI.h"
#include<iostream>
AI::AI() :x_(0), y_(0), w_(70), h_(70), AiW(10), AiH(10), box(), render(nullptr)
{
	Vec3 pos = Vec3(); 
	Vec3 vel = Vec3(2.0f, 1.0f,0.0f); 
	Vec3 accel = Vec3();  
	float orientation = 0.0f; 
	float rotation = 0.0f; 
	float angular = 0.0f; 
	float maxRotation = 1.0f;
	float maxSpeed = 5.0f; 

	body = new Body();
}

AI AI::getPlayer()
{


	return AI();
}

AI::~AI()
{

}

bool AI::OnCreate()
{


	steering = new Steering();

	//-------------------------------
	/// Boxes setup 
	int Rows = 6;
	int Cols = 6;
	box.resize(Rows * Cols);  
	int index = 0;
	for (int j = 0; j < Rows; j++) {
		for (int i = 0; i < Cols; i++) {

			x_ = 300 + i * w_;  
			y_ = 100 + j * w_; 
			box[index].x = x_;       
			box[index].y = y_;  
			box[index].w = w_;    
			box[index].h = h_;   

			++index;
		}
	}

	randomAI.x = AiX;
	randomAI.y = AiY;
	randomAI.w = AiW;
	randomAI.h = AiH;

	for (int i = 0; i < box.size();i++) {
		if (checkCollision(randomAI, box[i])) {

			std::cout << "Hit\n";
		}
	}
	
	return true;
}

void AI::OnDestroy()
{


	//delete body;

	delete& randomAI;
	delete& box;
}

void AI::Draw(SDL_Renderer* renderer_)
{

	render = renderer_;
	SDL_SetRenderDrawColor(renderer_, 255, 255, 255, 255);
	for (size_t i = 0; i < box.size(); i++) {
		SDL_RenderDrawRect(renderer_, &box[i]);
	}



	for (size_t i = 0; i < box.size(); i++) {
		if (isClick[i]) {
			// If this rectangle was clicked, fill it with white
			SDL_SetRenderDrawColor(renderer_, 0, 255, 0, 255);
			SDL_RenderFillRect(renderer_, &box[i]);
		}

	}

	SDL_SetRenderDrawColor(renderer_, 255, 0, 0, 255);

	SDL_RenderDrawRect(renderer_, &randomAI);

	SDL_RenderFillRect(renderer_, &randomAI);

}

void AI::HandelEvent(SDL_Event event_)
{
	if (SDL_MOUSEBUTTONDOWN == event_.type) {
		if (SDL_BUTTON_LEFT == event_.button.button) {
			SDL_GetMouseState(&mouse_x, &mouse_y);

			// Check if the mouse click is inside any of the rectangles
			for (size_t i = 0; i < box.size(); i++) {
				if (mouse_x >= box[i].x && mouse_x <= (box[i].x + box[i].w) &&
					mouse_y >= box[i].y && mouse_y <= (box[i].y + box[i].h)) {


					isClick[i] = !isClick[i];
				}
			}

		}
	}

}

void AI::Update(float deltaTime)
{

	static float speed = 1.0;     
	speed += deltaTime;    
	
	/*randomAI.x += (speed * 5.0f);   
	randomAI.y += (speed * 5.0f);   */

	PhysicsEquation(deltaTime,Vec3(randomAI.x, randomAI.y, 0.0f)); 
	randomAI.x += vel.x;  
	randomAI.y += vel.y;   

	for (int i = 0; i < box.size();i++) { 
		if (checkCollision(randomAI, box[i])) {  
			std::cout << "Collision detected with box " << i << "\n"; 
			result.Update(steering, deltaTime);
			

		} 
	}
}

bool AI::checkCollision(SDL_Rect rect1, SDL_Rect rect2)
{

	if (rect1.x + rect1.w <rect2.x || rect1.x >rect2.x + rect2.w || rect1.y + rect1.h 
		< rect2.y || rect1.y > rect2.y + rect2.h) {
		return false; 
	}
	else {
		std::cout << "HIT\n"; 

	}
	return true;
}

Vec3 AI::getRandomAIPos()
{

	
	return Vec3(randomAI.x, randomAI.y, 0.0f);  
	 

}

std::vector<Vec3> AI::getBoxesPos()
{
	std::vector<Vec3> positions;
	for (const auto& b : box) {
		positions.emplace_back(b.x, b.y, 0.0f);
	}
	return positions;
}

Kinematic AI::getSteering()
{
	for (int i = 0; i < box.size(); i++) {
	result.velocity = Vec3(randomAI.x, randomAI.y, 0.0f) - Vec3(box[i].x, box[i].y,0.0f);
}
	VMath::normalize(result.velocity); 

	result.velocity *= maxSpeed; 
	result.rotation = 1.0f; 
	return result;
}

void AI::PhysicsEquation(float deltaTime, Vec3 initialPos) 
{
	// Use initial position from the caller
	pos = initialPos; 

	// Update position based on velocity and acceleration
	pos = pos + vel * deltaTime + accel * (0.5f * deltaTime * deltaTime); 
	vel = vel + accel * deltaTime;

	// Clip to maxSpeed, if needed
	if (VMath::mag(vel) > maxSpeed) { 
		vel = VMath::normalize(vel) * maxSpeed; 
	}

	// Update orientation and apply maxRotation constraints
	orientation += rotation * deltaTime; 
	rotation += angular * deltaTime; 
	if (rotation > maxRotation) rotation = maxRotation; 

	// Print debugging info to ensure proper movement
	std::cout << "New position: (" << pos.x << ", " << pos.y << ")\n"; 
	std::cout << "Velocity: (" << vel.x << ", " << vel.y << ")\n"; 

}
