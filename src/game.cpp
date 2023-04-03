#include "game.hpp"
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
using namespace std;

Game::Game(const char* title, int x, int y, int w, int h, Uint32 flags)
:window(NULL), renderer(NULL)
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
    while(gameState != GameState::EXIT){
        prepareScene(); // sets up rendering
        handleEvents(); // collects and precesses user input
        presentScene(); // displays scene
        SDL_Delay(16); // limits fps to around 62fps
    }

    SDL_Quit();
}

void Game::handleEvents(){
    SDL_Event evnt;
    SDL_PollEvent(&evnt);

    switch(evnt.type){
        case SDL_QUIT:
            gameState = GameState::EXIT;
            break;
    }
}

void Game::prepareScene(){
    SDL_SetRenderDrawColor(renderer, 96, 128, 255, 255);
	SDL_RenderClear(renderer);
}

void Game::presentScene(){
    SDL_RenderPresent(renderer);
}