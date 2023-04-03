#include <iostream>
#include "game.hpp"
using namespace std;

int main(int argc, char* argv[]){
   int screenWidth = 1280;
   int screenHeight = 720;

   Game game("Falcon Fury", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);

   game.run();

    return 0;
}

// mimgw32-make -f .\MakeFile
// .\Main.exe