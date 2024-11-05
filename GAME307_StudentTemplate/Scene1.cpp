#include "Scene1.h"


Scene1::Scene1(SDL_Window* sdlWindow_, GameManager* game_) {
	window = sdlWindow_;
	game = game_;
	renderer = SDL_GetRenderer(window);
	xAxis = 6.0f;
	yAxis = 6.0f;

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
	//ai->OnCreate();
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
		//blinky->setTextureWith("Blinky.png");// Assume you've modified setTexture to accept an SDL_Texture*

		//Pathfinding---------------------------------------------------
		
		createTiles();
		
		graph = new Graph();
		if (!graph->OnCreate(sceneNodes)) {
			// error message
			return false;
		}

		calculateConnectionWeight();  
		//graph->addWeightedConnection(sceneNodes[18], sceneNodes[19], 4.1f); // this for path B . calculating the small numbers in order to reach the path 		 
		//graph->addWeightedConnection(sceneNodes[19], sceneNodes[20], 5.0f);	// this for path B . calculating the small numbers in order to reach the path
		//graph->addWeightedConnection(sceneNodes[20], sceneNodes[21], 7.5f);	// this for path B . calculating the small numbers in order to reach the path
		//graph->addWeightedConnection(sceneNodes[21], sceneNodes[22], 3.0f);	// this for path B . calculating the small numbers in order to reach the path	  
		//graph->addWeightedConnection(sceneNodes[22], sceneNodes[16], 2.5f); // this for path B . calculating the small numbers in order to reach the path
		//graph->addWeightedConnection(sceneNodes[16], sceneNodes[11], 2.5f); // this for path B . calculating the small numbers in order to reach the path
		//																		


		//graph->addWeightedConnection(sceneNodes[18], sceneNodes[12], 2.1f); // this for path A . calculating the small numbers in order to reach the path 
		//graph->addWeightedConnection(sceneNodes[12], sceneNodes[13], 2.2f);	// this for path A . calculating the small numbers in order to reach the path 
		//graph->addWeightedConnection(sceneNodes[13], sceneNodes[14], 3.5f);	// this for path A . calculating the small numbers in order to reach the path 
		//graph->addWeightedConnection(sceneNodes[14], sceneNodes[15], 3.0f);	// this for path A . calculating the small numbers in order to reach the path 
		//graph->addWeightedConnection(sceneNodes[15], sceneNodes[16], 2.5f);	// this for path A . calculating the small numbers in order to reach the path 
		//graph->addWeightedConnection(sceneNodes[16], sceneNodes[11], 2.5f);	// this for path A . calculating the small numbers in order to reach the path 

		
			std::vector<Node*> path = graph->findPath(sceneNodes[18], sceneNodes[11]); // the starting and end point is from 18 to 11 node.   
	   
	// end of character set ups
	
	return true;
}

void Scene1::createTiles()
{
	tileWidth = 1.0f;
	tileHeight = 1.0f;

	// resize
	int cols = ceil(xAxis - 0.5 * tileWidth / tileWidth);
	int rows = ceil(yAxis - 0.5 * tileHeight / tileHeight);

	tiles.resize(rows);
	for (int i = 0; i < rows; i++)
	{
		tiles[i].resize(cols);

	}

	sceneNodes.resize(cols * rows);

	Node* n;
	int label = 0;
	Tile* t;
	int i, j;

	i = 0;
	j = 0;

	for (float y = 0.5f * tileHeight; y < yAxis; y += tileHeight)
	{
		// do stuff as y increases
		for (float x = 0.5f * tileWidth; x < xAxis; x += tileWidth)
		{
			// do stuff as x increases

			//create tile
			n = new Node(label);
			sceneNodes[label] = n;
			Vec3 tilepos = Vec3(x, y, 0.0f);
			t = new Tile(n, tilepos, tileWidth, tileHeight, this);
			tiles[i][j] = t;
			if (sceneNodes[label]->getLabel() == sceneNodes[label]->getLabel()) { 

				t->color_ = true;
			} 
			j++;
			label++;
			
		}
		j = 0;
		i++;
	}
	
}

void Scene1::calculateConnectionWeight()
{
	int rows = tiles.size();
	int cols = tiles[0].size();

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{

			Tile* fromTile = tiles[i][j];
			Node* from = fromTile->getNode();

			//left
			if (j >= 1)
			{
				Node* to = tiles[i][j - 1]->getNode();
				graph->addWeightedConnection(from, to, tileWidth);
			}

			//right
			if ((j + 1) < cols) {  
				Node* to = tiles[i][j + 1]->getNode();
				graph->addWeightedConnection(from, to, tileWidth);
			}
			//above
			if ((i + 1) < rows)
			{
				Node* to = tiles[i + 1][j]->getNode();
				graph->addWeightedConnection(from, to, tileHeight);
			}

			if ((i - 1 ) >= 0) {
				Node* to = tiles[i - 1][j]->getNode(); 

				graph->addWeightedConnection(from , to, tileHeight); 
			}
			//below
		}
	}

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
	
		//blinky->Update(deltaTime); 

	//ai->Update(deltaTime);
	// Update player
	//game->getPlayer()->Update(deltaTime);



}

void Scene1::Render() {
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	// render any npc's
	
	//	blinky->render(0.15f); 

		//render tiles
		for (int i = 0; i < tiles.size(); i++) {
			for (int j = 0; j < tiles[i].size(); j++)
			{
				tiles[i][j]->Render();
				
			}
		}
		SDL_RenderPresent(renderer);

	// render the player
	//game->RenderPlayer(0.10f);
//	ai->Draw(renderer); 
	SDL_RenderPresent(renderer);
}

void Scene1::HandleEvents(const SDL_Event& event)
{
	// send events to npc's as needed
	//ai->HandelEvent(event);  
	// send events to player as needed
	game->getPlayer()->HandleEvents(event);
}
