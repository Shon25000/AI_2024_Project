#include "Scene1.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 25.0f;
	yAxis = 15.0f;
	ai = new AI();
	// create a NPC
	/*blinky = nullptr;*/
}

Scene1::~Scene1() {}

bool Scene1::OnCreate() {
	int w, h;
	SDL_GetWindowSize(window, &w, &h);

	Matrix4 ndc = MMath::viewportNDC(w, h);
	Matrix4 ortho = MMath::orthographic(0.0f, xAxis, 0.0f, yAxis, 0.0f, 1.0f);
	projectionMatrix = ndc * ortho;

	/// Turn on the SDL imaging subsystem
	IMG_Init(IMG_INIT_PNG);

	// Set player image to PacMan

	SDL_Surface* image;
	SDL_Texture* texture;
	ai->OnCreate();
	image = IMG_Load("pacman.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
	game->getPlayer()->setImage(image);
	game->getPlayer()->setTexture(texture);

	// Set up characters, choose good values for the constructor
	// or use the defaults, like this

	 
	
		blinky = new Character();
		if (!blinky->OnCreate(this)) {
			return false;
		}
		blinky->setTextureWith("Blinky.png");// Assume you've modified setTexture to accept an SDL_Texture*
	
	// end of character set ups

	return true;
}

void Scene1::OnDestroy()
{
	/*if (blinky)
	{
		blinky->OnDestroy();
		delete blinky;
	}*/
}

void Scene1::Update(const float deltaTime) {
	// Calculate and apply any steering for npc's
	
		blinky->Update(deltaTime); 

	ai->Update(deltaTime);
	// Update player
	game->getPlayer()->Update(deltaTime);



}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	
		blinky->render(0.15f); 

	// render the player
	game->RenderPlayer(0.10f);
	ai->Draw(renderer); 
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed
	ai->HandelEvent(event);  
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
