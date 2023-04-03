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
        void doKeyUp(SDL_KeyboardEvent *event);
        void doKeyDown(SDL_KeyboardEvent *event);

        SDL_Window* window;
        SDL_Renderer* renderer;

        // Movement
        int up,down,left,right;

        GameState gameState;
};