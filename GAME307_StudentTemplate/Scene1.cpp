#include "Scene1.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_){
	window = sdlWindow_;
    game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
	  /*ai = new AI();*/
	// create a NPC
	blinky = nullptr;
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window,&w,&h);
	
	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;
	
	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan
	ai.OnCreate(); 
	SDL_Surface* image;
	SDL_Texture* texture;

	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this
	blinky = new Character();
	if (!blinky->OnCreate(this) || !blinky->setTextureWith("Blinky.png") )
	{
		return false;
	}

	// end of character set ups

	return true;
}

void Scene1::OnDestroy() 
{
	if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}
}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	//blinky->Update(deltaTime);
	SteeringOutput* steering; 
	steering = NULL; 
	// Update player
	ai.Update(deltaTime); 
	//SteeringBehaviour* steeringAlqorthim = new Seek(body, body->);   
	//if (VMath::distance(ai->getPlayer().getPos(), body->getPos()) > 5.0f) {  
	//	steering = steeringAlqorthim->getSteering(); 

	//	body->Update(deltaTime, steering); 
	//}
	//game->getPlayer()->Update(deltaTime);
}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	//blinky->render(0.15f);
	ai.Draw(renderer); 
	// render the player
	
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed
	ai.HandelEvent(event); 
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
