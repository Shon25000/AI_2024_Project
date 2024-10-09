#define AI_H
#ifdef  AI_H
#include<SDL.h>
#include<SDL_rect.h>
#include<vector> 
#include"Body.h"
class AI 

{
public:
	
	AI();
    ~AI(); 
	Body* body; 
	AI getPlayer();
	
	bool OnCreate();
	void OnDestroy();
	void Draw(SDL_Renderer* renderer_);

	void HandelEvent(SDL_Event event_);
	void Update(float deltaTime);

	
	bool checkCollision(SDL_Rect rect1, SDL_Rect rect2); 

	std::vector<Vec3> getBoxesPos();


private:
	// Physics stuff
	Vec3 pos;
	Vec3 vel;  
	Vec3 accel; 
	float orientation; 
	float rotation; 
	float angular; 
	float maxRotation; 
	float maxSpeed; 
//------- Rects stuff 
	int x_, y_, w_, h_; 
	int AiX, AiY, AiW, AiH;
	std::vector <SDL_Rect> box;   
// ----- Mouse stuff 
	int mouse_x, mouse_y;
	bool isClick[35];
	
	// Render 
	SDL_Renderer* render;
	SDL_Window* window;

};

#endif //  AI_H
