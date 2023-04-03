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
        void prepareScene(); // prepares render
        void presentScene(); // displays render
        SDL_Texture *loadTexture(char *filename); // loads an image
        void blit(SDL_Texture *texture, int x, int y); // displays an image

        SDL_Window* window;
        SDL_Renderer* renderer;

        GameState gameState;
};