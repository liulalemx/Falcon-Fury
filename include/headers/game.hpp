#pragma once

#include <iostream>
#include <sdl2/SDL.h>
#include <sdl2/SDL_image.h>

enum class GameState {PLAY, EXIT};

class Game{
    public:
        Game(); 
        ~Game();
        void run(); // runs the game
        
    private:
        void init(const char* title, int x, int y, int w, int h, Uint32 flags); // initialize modules
        void gameLoop(); // main game loop
        void handleEvents(); // handles game events

        SDL_Window* _window;
        SDL_Renderer* _renderer;

        int _screenWidth;
        int _screenHeight;

        GameState _gameState;
};
