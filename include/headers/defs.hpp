#pragma once

#define PLAYER_SPEED          8
#define PLAYER_BULLET_SPEED   16

#define MAX_KEYBOARD_KEYS 350

#define SIDE_PLAYER 0
#define SIDE_ALIEN  1

#define MAX_SND_CHANNELS 8

#define MAX_LINE_LENGTH 1024

enum
{
	CH_ANY = -1,
	CH_PLAYER,
	CH_ALIEN_DIE,
    CH_ALIEN_HIT
};

