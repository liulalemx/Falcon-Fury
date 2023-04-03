#include <SDL.h>

struct Entity {
	int x = 0;
	int y = 0;
    int dx = 0;
    int dy = 0;
    int health = 0;
	SDL_Texture *texture;
};