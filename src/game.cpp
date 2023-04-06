#include "game.hpp"
#include "structs.hpp"
#include "defs.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstdlib>
using namespace std;

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags)
:window(NULL), renderer(NULL), up(0), down(0), left(0), right(0), fire(0)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0) cout << "SDL_INIT HAS FAILED! SDL_ERROR: "<< SDL_GetError() << endl;

    window = SDL_CreateWindow(title, x, y, w, h, flags);

    if(window == NULL) cout << "Window failed to open. Error: " << SDL_GetError() << endl;

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(window == NULL) cout << "Render failed to create. Error: " << SDL_GetError() << endl;
};

Game::~Game(){};

void Game::run(){
    gameLoop();
}

void Game::gameLoop(){
    Entity player;

	Entity bulletHead;
    Entity *bulletTail = new Entity();
	bulletTail = &bulletHead;

	Entity fighterHead;
    Entity *fighterTail = new Entity();
	fighterTail = &fighterHead;

	int enemySpawnTimer = 0;

    player.x = 500;
    player.y = 640;
    player.dx = 0;
    player.dy = 0;
	player.side = SIDE_PLAYER;
    player.texture = loadTexture((char*)"res/images/player.png");
	SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);

	// Cache enemy and bullet textures
    SDL_Texture *bulletTexture = loadTexture((char*)"res/images/bullet.png");
    SDL_Texture *enemyTexture1 = loadTexture((char*)"res/images/enemyShip.png");
    SDL_Texture *enemyTexture2 = loadTexture((char*)"res/images/enemyShip_lvl2.png");
    SDL_Texture *enemyTexture3 = loadTexture((char*)"res/images/enemyShip_lvl3.png");
    SDL_Texture *enemyTexture4 = loadTexture((char*)"res/images/enemyShip_lvl4.png");
    SDL_Texture *enemyTexture5 = loadTexture((char*)"res/images/enemyShip_lvl5.png");
    SDL_Texture *enemyTexture6 = loadTexture((char*)"res/images/enemyShip_lvl6.png");

    while(gameState != GameState::EXIT){
        prepareScene(); // sets up rendering
        handleEvents(); // collects and precesses user input

        player.x += player.dx;
        player.y += player.dy;

        // Player key input
		if(player.reload > 0) player.reload--;

        if (up)
		{
			player.y -= 4;
		}

		if (down)
		{
			player.y += 4;
		}

		if (left)
		{
			player.x -= 4;
		}

		if (right)
		{
			player.x += 4;
		}

		// allow fire bullet every 8 frames
        if(fire && player.reload == 0){
			player.reload = 8;

			// Create bullet
			Entity *bullet = new Entity();
    		memset(bullet, 0, sizeof(Entity));

			bulletTail->next = bullet;
			bulletTail = bullet;

            bullet->x = player.x + 8;
            bullet->y = player.y;
            bullet->dx = 0;
            bullet->dy = -PLAYER_BULLET_SPEED;
            bullet->health = 1;
			bullet->side = SIDE_PLAYER;
			bullet->texture = bulletTexture;
			SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h); 
        }

		// generate enemy ships every 0.5 - 1.5 seconds
		if (--enemySpawnTimer <= 0)
		{
			Entity *enemy = new Entity();
			memset(enemy, 0, sizeof(Entity));
			fighterTail->next = enemy;
			fighterTail = enemy;

			enemy->x = rand() % 1280;
			enemy->y = 0;
			enemy->side = SIDE_ALIEN;

			// Load different enemy
			int enemyType = rand() % 5;
			switch (enemyType)
			{
				case 0:
					enemy->texture = enemyTexture1;
					SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
					enemy->health = 1;
					break;
				case 1:
					enemy->texture = enemyTexture2;
					SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
					enemy->health = 2;
					break;
				case 2:
					enemy->texture = enemyTexture3;
					SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
					enemy->health = 3;
					break;
				case 3:
					enemy->texture = enemyTexture4;
					SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
					enemy->health = 4;
					break;
				case 4:
					enemy->texture = enemyTexture5;
					SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
					enemy->health = 5;
					break;
				case 5:
					enemy->texture = enemyTexture6;
					SDL_QueryTexture(enemy->texture, NULL, NULL, &enemy->w, &enemy->h);
					enemy->health = 6;
					break;
				default:
					break;
			}


			

			enemy->dy = (2 + (rand() % 4));

			enemySpawnTimer = 30 + (rand() % 60);
		}

		// handle physics and render for each bullet
		Entity *b = new Entity();
		Entity *prev = new Entity();
		prev = &bulletHead;

		for (b = bulletHead.next ; b != NULL ; b = b->next){
        	b->x += b->dx;
        	b->y += b->dy;

			blit(b->texture, b->x, b->y);
			
			if(b->y < 0 || bulletHitFighter(b, fighterHead)){
				if (b == bulletTail)
				{
					bulletTail = prev;
				}
				prev->next = b->next;
				delete b;
				b = prev;
			}

			prev = b;

		}

		// handle physics and render for each enemy
		Entity *e = new Entity();
		Entity *prevv = new Entity();
		prevv = &fighterHead;

		for (e = fighterHead.next ; e != NULL ; e = e->next){
        	e->x += e->dx;
        	e->y += e->dy;

			blit(e->texture, e->x, e->y);
			
			if( e->y > 720 || e->health == 0){
				if (e == fighterTail)
				{
					fighterTail = prevv;
				}
				prevv->next = e->next;
				delete e;
				e = prevv;
			}

			prevv = e;
		}
			
        blit(player.texture, player.x, player.y); // display image


        presentScene(); // displays scene
        SDL_Delay(16); // limits fps to around 62fps
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Game::handleEvents(){
    SDL_Event evnt;
    
    while(SDL_PollEvent(&evnt)){
        switch(evnt.type){
            case SDL_QUIT:
                gameState = GameState::EXIT;
                break;
            case SDL_KEYDOWN:
                doKeyDown(&evnt.key);
                break;
            case SDL_KEYUP:
                doKeyUp(&evnt.key);
                break;
            default:
                break;
        }
    }  
}

void Game::prepareScene(){
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}

void Game::presentScene(){
    SDL_RenderPresent(renderer);
}

SDL_Texture * Game::loadTexture(char *filename)
{
	SDL_Texture *texture = NULL;

	SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

	texture = IMG_LoadTexture(renderer, filename);

	return texture;
}

void Game::blit(SDL_Texture *texture, int x, int y)
{
	SDL_Rect dest;

	dest.x = x;
	dest.y = y;
	SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);

	SDL_RenderCopy(renderer, texture, NULL, &dest);
}

void Game::doKeyDown(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
        
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
	        fire = 1;
        }

		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			up = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			down = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
			left = 1;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			right = 1;
		}
	}
}

void Game::doKeyUp(SDL_KeyboardEvent *event)
{
	if (event->repeat == 0)
	{
        if (event->keysym.scancode == SDL_SCANCODE_SPACE)
        {
	        fire = 0;
        }

		if (event->keysym.scancode == SDL_SCANCODE_UP)
		{
			up = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_DOWN)
		{
			down = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_LEFT)
		{
		    left = 0;
		}

		if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
		{
			right = 0;
		}
	}
}

int Game::collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2){
	return (max(x1, x2) < min(x1 + w1, x2 + w2)) && (max(y1, y2) < min(y1 + h1, y2 + h2));
}

int Game::bulletHitFighter(Entity *b, Entity fighterHead) // checks if a bullet has hit an enemy figher using collision function
{
	Entity *e;

	for (e = fighterHead.next ; e != NULL ; e = e->next)
	{
		if (e->side != b->side && collision(b->x, b->y, b->w, b->h, e->x, e->y, e->w, e->h))
		{
			b->health = 0;
			e->health--;

			return 1;
		}
	}

	return 0;
}