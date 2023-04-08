#include "sound.hpp"
#include <SDL_mixer.h>
#include "defs.hpp"
#include <iostream>

void Sound::initSounds()
{
	loadSounds();
}

void Sound::loadSounds(){

    if (GAME_MUSIC != NULL)
	{
		Mix_HaltMusic();
		Mix_FreeMusic(GAME_MUSIC);
		GAME_MUSIC = NULL;
	}

	GAME_MUSIC = Mix_LoadMUS("res/sounds/gameMusic.wav");

    SND_PLAYER_FIRE = Mix_LoadWAV("res/sounds/shoot.wav");
    SND_PLAYER_DIE = Mix_LoadWAV("res/sounds/playerDeath.wav");
    SND_ALIEN_DIE = Mix_LoadWAV("res/sounds/explosion.wav");
    SND_ALIEN_HIT = Mix_LoadWAV("res/sounds/enemyHit.wav");
}

void Sound::playMusic(int loop)
{
	Mix_PlayMusic(GAME_MUSIC, (loop) ? -1 : 0);
	Mix_VolumeMusic(25);
}

void Sound::playSound(Mix_Chunk *sound, int channel)
{
	Mix_PlayChannel(channel, sound, 0);
	Mix_VolumeChunk(sound, 25);
}