#include "Character.h"
#include"Flee.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	body.resize(2); 
	// Configure and instantiate the body to use for the demo
	for (size_t i = 0; i < body.size(); i++) {
		if (!body[i])
		{
			float radius = 0.2;
			float orientation = 0.0f;
			float rotation = 0.0f;
			float angular = 0.0f;
			float maxSpeed = 4.0f;
			float maxAcceleration = 10.0f;
			float maxRotation = 2.0f;
			float maxAngular = 10.0f;
			body[i] = new KinematicBody(
				Vec3(10.0f, 5.0f, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), 1.0f,
				radius,
				orientation,
				rotation,
				angular,
				maxSpeed,
				maxAcceleration,
				maxRotation,
				maxAngular
			);
		}


		if (!body[i])
		{
			return false;
		}
	}
	return true;
}

void Character::OnDestroy()
{
	for (size_t i = 0; i < body.size(); i++) { 
		if (body[i])
		{
			if (body[i]->getTexture())
			{
				SDL_DestroyTexture(body[i]->getTexture());
			}
			delete body[i];

		}
	}
};

bool Character::setTextureWith(string file)
{
	for (size_t i = 0; i < body.size(); i++) {
		SDL_Surface* image = IMG_Load(file.c_str());
		if (image == nullptr) {
			std::cerr << "Can't open the image" << std::endl;
			return false;
		}
		SDL_Window* window = scene->getWindow();
		SDL_Renderer* renderer = SDL_GetRenderer(window);
		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, image);
		if (!texture)
		{
			std::cerr << "Can't create texture" << std::endl;
			return false;
		}
		if (body[i]->getTexture()) SDL_DestroyTexture(body[i]->getTexture());
		body[i]->setTexture(texture);
		SDL_FreeSurface(image);
	}
	return true;
}

void Character::Update(float deltaTime)
{
	// create a new overall steering output
	for (size_t i = 0; i < body.size(); i++) {

		// Create a new steering output for each body
		SteeringOutput* steering = new SteeringOutput();
		steerToSeekPlayer(steering);  // Pass the index to steerToSeekPlayer for specific body[i]

		body[i]->Update(deltaTime, steering);

		// Clean up memory
		delete steering;
	}

}

void Character::steerToSeekPlayer(SteeringOutput* steering)
{
	// set the target for steering; target is used by the steerTo... functions
	// (often the target is the Player)

	// using the target, calculate and set values in the overall steering output

	/*SteeringBehaviour* fleeAlqorthim = new Flee(body, scene->game->getPlayer());
	if (VMath::distance(scene->game->getPlayer()->getPos() , body->getPos()) < 5.0f) {
		*steering += *(fleeAlqorthim->getSteering());

		body->Update(deltaTime, steering);
	}*/
	for (size_t i = 0; i < body.size(); i++) {
		// Create a seek algorithm for the specific body[i]
		SteeringBehaviour* seekAlgorithm = new Seek(body[i], scene->game->getPlayer()); 
		*steering += *(seekAlgorithm->getSteering()); 
		
		// Clean up the seek algorithm memory
		delete seekAlgorithm;
		//TODO: error handling of the new fails 
	}
	/*SteeringBehaviour* steeringAlqorthim = new Seek(body,scene->game->getPlayer());
	if (VMath::distance(scene->game->getPlayer()->getPos() , body->getPos()) > 5.0f) {
		steering = steeringAlqorthim->getSteering();

		body->Update(deltaTime, steering);
	}*/

	// apply the steering to the equations of motion



	// clean up memory
	// (delete only those objects created in this function)

	/*if (seekAlqorthim) {
		delete seekAlqorthim;
	}*/

}

void Character::HandleEvents(const SDL_Event& event)
{
	// handle events here, if needed
}

void Character::render(float scale) const
{
	SDL_Renderer* renderer = scene->game->getRenderer();
	Matrix4 projectionMatrix = scene->getProjectionMatrix();

	std::vector<SDL_Rect> square;
	Vec3 screenCoords;
	Vec3 screenCoords2;
	int    w, h;
	for (size_t i = 0; i < body.size(); i++) {
	// notice use of "body" in the following
	SDL_QueryTexture(body[i]->getTexture(), nullptr, nullptr, &w, &h);


	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	
	square.resize(2); 
	for (int i = 0; i < square.size(); i++) {
		screenCoords = projectionMatrix * body[0]->getPos();
		screenCoords2 = projectionMatrix * body[1]->getPos();
		/*square.x = static_cast<int>(screenCoords.x - 0.5f * w);
		square.y = static_cast<int>(screenCoords.y - 0.5f * h);*/
		square[0].x = static_cast<int>(screenCoords.x - 0.0f * w);
		square[0].y = static_cast<int>(screenCoords.y - 0.0f * h);
		square[0].x = static_cast<int>(screenCoords2.x - 0.10f * w);
		square[0].y = static_cast<int>(screenCoords2.y - 0.10f * h);
		square[i].w = w;
		square[i].h = h;

		// Convert character orientation from radians to degrees.
		float orientation = body[i]->getOrientation() * 180.0f / M_PI;   
		SDL_RenderCopyEx(renderer, body[i]->getTexture(), nullptr, &square[i],  
			orientation, nullptr, SDL_FLIP_NONE); 
		

		SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

		SDL_RenderDrawRect(renderer, &square[i]);
	}
	}
}
