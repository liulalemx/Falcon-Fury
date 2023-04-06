#include "game.hpp"
#include "structs.hpp"
#include "defs.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <cstring>
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

    player.x = 500;
    player.y = 640;
    player.dx = 0;
    player.dy = 0;
    player.texture = loadTexture((char*)"res/images/player.png");
	SDL_QueryTexture(player.texture, NULL, NULL, &player.w, &player.h);

    SDL_Texture *bulletTexture = loadTexture((char*)"res/images/bullet.png");

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
			bullet->texture = bulletTexture;
			SDL_QueryTexture(bullet->texture, NULL, NULL, &bullet->w, &bullet->h); 
        }

		// handle physics and render for each bullet
		
			Entity *b = new Entity();
			Entity *prev = new Entity();
			prev = &bulletHead;

			for (b = bulletHead.next ; b != NULL ; b = b->next){
        		b->x += b->dx;
        		b->y += b->dy;

				blit(b->texture, b->x, b->y);
			
				if(b->y < 0){
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