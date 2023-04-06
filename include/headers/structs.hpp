#pragma once
#include <SDL.h>
#include <iostream>

struct Entity {
	float x = 0;
	float y = 0;
    float dx = 0;
    float dy = 0;
    int w = 0;
    int h= 0;
    int reload = 0;
    int health = 0;
	SDL_Texture *texture;
    Entity *next = NULL;

    ~Entity(){
        std::cout << "Entity freed" <<std::endl;
    }
};
