#include "headers/game.hpp"
#include <SDL.h>
#include <SDL_image.h>

Game::Game()
:_window(nullptr), _renderer(nullptr), _screenWidth(1024), _screenHeight(600), _gameState(GameState::PLAY){};
Game::~Game(){};

void Game::run(){
    init("Falcon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);
    gameLoop();
}

void Game::init(const char* title, int x, int y, int w, int h, Uint32 flags){
    SDL_Init(SDL_INIT_EVERYTHING);

    _window = SDL_CreateWindow(title, x, y, w, h, flags);
    _renderer = SDL_CreateRenderer(_window, -1, 0);
}

void Game::gameLoop(){
    while(_gameState != GameState::EXIT){
        handleEvents();

    }
}

void Game::handleEvents(){
    SDL_Event evnt;
    SDL_PollEvent(&evnt);

    switch(evnt.type){
        case SDL_QUIT:
            _gameState = GameState::EXIT;
            break;
    }
}