#include "Character.h"
#include"Flee.h"

bool Character::OnCreate(Scene* scene_)
{
	scene = scene_;
	body.resize(5); 
	// Configure and instantiate the body to use for the demo
	for (size_t i = 0; i < body.size(); i++) {
		if (!body[0])
		{
			float radius = 0.2;
			float orientation = 0.0f;
			float rotation = 0.0f;
			float angular = 0.0f;
			float maxSpeed = 5.0f;
			float maxAcceleration = 10.0f;
			float maxRotation = 2.0f;
			float maxAngular = 10.0f;
			body[0] = new KinematicBody(
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

		if (!body[1])
		{
			float radius = 0.2;
			float orientation = 0.0f;
			float rotation = 0.0f;
			float angular = 0.0f;
			float maxSpeed = 4.0f;
			float maxAcceleration = 10.0f;
			float maxRotation = 2.0f;
			float maxAngular = 10.0f;
			body[1] = new KinematicBody(
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
		if (!body[2])
		{
			float radius = 0.2;
			float orientation = 0.0f;
			float rotation = 0.0f;
			float angular = 0.0f;
			float maxSpeed = 3.0f;
			float maxAcceleration = 10.0f;
			float maxRotation = 2.0f;
			float maxAngular = 10.0f;
			body[2] = new KinematicBody(
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
		if (!body[3])
		{
			float radius = 0.2;
			float orientation = 0.0f;
			float rotation = 0.0f;
			float angular = 0.0f;
			float maxSpeed = 2.0f;
			float maxAcceleration = 10.0f;
			float maxRotation = 2.0f;
			float maxAngular = 10.0f;
			body[3] = new KinematicBody(
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
		if (!body[4])
		{
			float radius = 0.2;
			float orientation = 0.0f;
			float rotation = 0.0f;
			float angular = 0.0f;
			float maxSpeed = 1.5f;
			float maxAcceleration = 10.0f;
			float maxRotation = 2.0f;
			float maxAngular = 10.0f;
			body[4] = new KinematicBody(
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
		ArrivePlayer(steering);   // Pass the index to steerToSeekPlayer for specific body[i]
		steerToSeekPlayer(steering); 
		body[i]->Update(deltaTime, steering);

		// Clean up memory
		delete steering;
	}

}

void Character::steerToSeekPlayer(SteeringOutput* steering)
{
	
	for (size_t i = 0; i < body.size(); i++) {

		SteeringBehaviour* seekAlgorithm = new Flee(body[i], scene->game->getPlayer());
		if (VMath::distance(scene->game->getPlayer()->getPos(), body[i]->getPos()) < 5.0f) {
			*steering += *(seekAlgorithm->getSteering());


		}
			SteeringBehaviour* fleeAlgorthim = new	Seek(body[i], scene->game->getPlayer());
		 if (VMath::distance(scene->game->getPlayer()->getPos(), body[i]->getPos()) > 5.0f) {

			 *steering += *(fleeAlgorthim->getSteering());
			}

		
	}


}

void Character::ArrivePlayer(SteeringOutput* steering)
{
	for (size_t i = 0; i < body.size(); i++) {
		SteeringBehaviour* arrive = new Arrive(body[i], scene->game->getPlayer());
		if (VMath::distance(scene->game->getPlayer()->getPos(), body[i]->getPos()) < 5.0f) {
			*steering += *(arrive->getSteering()); 

		}
	}

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
	Vec3 screenCoords3;
	Vec3 screenCoords4;
	Vec3 screenCoords5;
	int    w, h;
	for (size_t i = 0; i < body.size(); i++) {
	// notice use of "body" in the following
	SDL_QueryTexture(body[i]->getTexture(), nullptr, nullptr, &w, &h);


	w = static_cast<int>(w * scale);
	h = static_cast<int>(h * scale);
	
	square.resize(5); 
	for (int i = 0; i < square.size(); i++) {
		screenCoords = projectionMatrix * body[0]->getPos();
		screenCoords2 = projectionMatrix * body[1]->getPos();
		screenCoords3 = projectionMatrix * body[2]->getPos();
		screenCoords4 = projectionMatrix * body[3]->getPos();
		screenCoords5 = projectionMatrix * body[4]->getPos();
		/*square.x = static_cast<int>(screenCoords.x - 0.5f * w);
		square.y = static_cast<int>(screenCoords.y - 0.5f * h);*/
		square[0].x = static_cast<int>(screenCoords.x - 0.0f * w);
		square[0].y = static_cast<int>(screenCoords.y - 0.0f * h);
		square[1].x = static_cast<int>(screenCoords2.x - 0.10f * w);
		square[1].y = static_cast<int>(screenCoords2.y - 0.10f * h);
		square[2].x = static_cast<int>(screenCoords3.x - 0.5f * w);
		square[2].y = static_cast<int>(screenCoords3.y - 0.5f * h);
		square[3].x = static_cast<int>(screenCoords4.x - 0.3f * w);
		square[3].y = static_cast<int>(screenCoords4.y - 0.3f * h);
		square[4].x = static_cast<int>(screenCoords5.x - 0.15f * w);
		square[4].y = static_cast<int>(screenCoords5.y - 0.15f * h);
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
