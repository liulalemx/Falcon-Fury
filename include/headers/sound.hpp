#pragma once

#include <SDL_mixer.h>
#include "defs.hpp"

class Sound{
    public:
        void initSounds();
        void loadSounds();
        void playMusic(int loop);
        void playSound(Mix_Chunk *sound, int channel);

        //The music that will be played
        Mix_Music *GAME_MUSIC = NULL;

        //The sound effects that will be used
        Mix_Chunk *SND_PLAYER_FIRE = NULL;
        Mix_Chunk *SND_PLAYER_DIE = NULL;
        Mix_Chunk *SND_ALIEN_DIE = NULL;
        Mix_Chunk *SND_ALIEN_HIT = NULL;
        Mix_Chunk *SND_POWERUP = NULL;
};