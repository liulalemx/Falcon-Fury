#pragma once

#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <structs.hpp>

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
        int collision(int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2); // checks if two rectangles overlap
        int bulletHitFighter(Entity *b, Entity fighterHead); // checks if a bullet has hit an enemy figher using collision function

        SDL_Window* window;
        SDL_Renderer* renderer;

        // Movement
        int up,down,left,right;

        int fire;

        GameState gameState;
};