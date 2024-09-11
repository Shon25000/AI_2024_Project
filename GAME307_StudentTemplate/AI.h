#define AI_H
#ifdef  AI_H
#include<SDL.h>
#include<SDL_rect.h>
#include<vector>
class AI
{

public :
	AI();
   ~AI();
   bool OnCreate();
   void Draw(SDL_Renderer* render_); 

   void HandelEvent(SDL_Event event); 
private:
	int x, y , w, h ;  
	std::vector <SDL_Rect> box_X;
	std::vector <SDL_Rect> box_Y; 
	SDL_Renderer* render; 
};

#endif //  AI_H