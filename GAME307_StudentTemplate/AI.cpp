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

	
	return true;
}

void AI::OnDestroy()
{


	//delete body;

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


std::vector<Vec3> AI::getBoxesPos()
{
	std::vector<Vec3> positions;
	for (const auto& b : box) {
		positions.emplace_back(b.x, b.y, 0.0f);
	}
	return positions;
}


