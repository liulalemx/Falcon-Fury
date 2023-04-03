#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

enum class GameState {PLAY, EXIT};

class Game{
    public:
        Game(const char* title, int x, int y, int w, int h, Uint32 flags); 
        ~Game();
        void run(); // runs the game

    private:
        void gameLoop(); // main game loop
        void handleEvents(); // handles game events

        SDL_Window* _window;
        SDL_Renderer* _renderer;

        GameState _gameState;
};
