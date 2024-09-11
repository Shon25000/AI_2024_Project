#include "AI.h"
#include<iostream>
AI::AI():x(0) , y(0) ,w(70),h (70) , box_X() , box_Y(), render(nullptr)  
{ 

}

AI::~AI()
{
	
}

bool AI::OnCreate()
{

	 int Rows = 6;   
	 int Cols = 6;   
	box_X.resize(Rows * Cols); 
	int index = 0; 
	for (int j = 0; j < Rows; j++) { 
	for (int i = 0; i < Cols; i++) {

			x = 300 + i * w;
			y = 100 + j * w;
			box_X[index].x = x; 
			box_X[index].y = y;  
			box_X[index].w = w; 
			box_X[index].h = h; 

			++index; 
		}
	 }

	return true;
}

void AI::Draw(SDL_Renderer* render_) 
{
	
	SDL_SetRenderDrawColor(render_, 255, 255, 255, 255); 
	for (size_t i = 0; i  < box_X.size();i++)  {   
		SDL_RenderDrawRect(render_, &box_X[i]);   
	} 
	for (size_t i = 0; i < box_Y.size(); i++) { 
		SDL_RenderDrawRect(render_, &box_Y[i]); 
	}
}

void AI::HandelEvent(SDL_Event event)
{


}
