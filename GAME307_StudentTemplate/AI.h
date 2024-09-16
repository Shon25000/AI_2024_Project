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

   void HandelEvent(SDL_Event event_); 
  
private:
	int x, y , w, h ;  

	int mouse_x, mouse_y; 
	bool isClick[35];   

	std::vector <SDL_Rect> box;
	SDL_Renderer* render; 
	SDL_Window* window;  
};

#endif //  AI_H