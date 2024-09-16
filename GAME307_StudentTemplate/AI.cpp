#include "AI.h"
#include<iostream>
AI::AI():x(0) , y(0) ,w(70),h (70) , box(), render(nullptr)  
{ 

}

AI::~AI()
{
	
}

bool AI::OnCreate()
{

	 int Rows = 6;   
	 int Cols = 6;   
	box.resize(Rows * Cols); 
	int index = 0; 
	for (int j = 0; j < Rows; j++) { 
	for (int i = 0; i < Cols; i++) {

			x = 300 + i * w;
			y = 100 + j * w;
			box[index].x = x; 
			box[index].y = y;  
			box[index].w = w; 
			box[index].h = h; 

			++index; 
		}
	 }

	return true;
}

void AI::Draw(SDL_Renderer* render_) 
{
	
	render = render_;
	SDL_SetRenderDrawColor(render_, 255, 255, 255, 255);
	for (size_t i = 0; i < box.size(); i++) {
		SDL_RenderDrawRect(render_, &box[i]);
	}



	for (size_t i = 0; i < box.size(); i++) {
		if (isClick[i]) {
			// If this rectangle was clicked, fill it with white
			SDL_SetRenderDrawColor(render_, 0, 255, 0, 255);
			SDL_RenderFillRect(render_, &box[i]); 
		}

	}
	
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