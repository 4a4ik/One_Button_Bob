#ifndef _INCLUDES_H
#define _INCLUDES_H


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

//160 x 120

#define TILE_TYPES 12
#define MAGNIFY 4

#define WALL 0
#define TORCH 1
#define LAVA 2
#define LEDDER 3
#define ARROW 4
#define BOMB 5
#define BAT 6
#define GHOST 7
#define PLATFORM 8
#define SPIKE_CEILING 9
#define ROCK 10
#define BOSS 11

#define DELETE 0
#define PLACE 1

#define MAN_WIDTH 10
#define MAN_HEIGHT 13

#define TORCH_WIDTH 15
#define TORCH_HEIGHT 16

#define LAVA_WIDTH 9
#define LAVA_HEIGHT 7

#define ARROW_WIDTH 5
#define ARROW_HEIGHT 6

#define BOMB_WIDTH 7
#define BOMB_HEIGHT 10

#define BAT_WIDTH 7
#define BAT_HEIGHT 5

#define GHOST_WIDTH 13
#define GHOST_HEIGHT 13

#define PLATFORM_WIDTH 10
#define PLATFORM_HEIGHT 4

#define SPIKE_CEILING_WIDTH 160
#define SPIKE_CEILING_HEIGHT 70

#define LEDDER_WIDTH 8
#define LEDDER_HEIGHT 40

#define ROCK_WIDTH 7
#define ROCK_HEIGHT 7

#define BOSS_WIDTH 23
#define BOSS_HEIGHT 27

#define EXPLOSION_WIDTH 130
#define EXPLOSION_HEIGHT 130

#define SPEAKER_X 545
#define SPEAKER_Y 6
#define SPEAKER_W 8
#define SPEAKER_H 8

#define PAUSE_X 593
#define PAUSE_Y 6
#define PAUSE_W 8
#define PAUSE_H 8

#define FORCE_METER_W 14
#define FORCE_METER_H 4

#define LIFE_METER_W 150
#define LIFE_METER_H 8

#define SCORE_W 22
#define SCORE_H 31


#define CLICK_SHOOT 0
#define CLICK_STOP 1
#define CLICK_ACCELERATE 2
#define CLICK_JUMP 3
#define CLICK_JUMP_STOP 4
#define CLICK_LEDDER 5
#define CLICK_BOSS 6
#define END 7

#include<SDL.h>
#include<SDL_image.h>
#include<SDL_mixer.h>
#include<SDL_ttf.h>

#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<fstream>
#include<ctime>

//The sound effects that will be used
extern	Mix_Music *music;
extern	Mix_Music *victory_music;

extern	Mix_Chunk *jump_sound;
extern	Mix_Chunk *dead_sound;
extern	Mix_Chunk *boomerang_sound;
extern	Mix_Chunk *explosion_sound;
extern	Mix_Chunk *boss_dead_sound;
extern	Mix_Chunk *boss_dead_sound2;
extern	Mix_Chunk *ghost_sound;
extern	Mix_Chunk *hurt_sound;

extern bool ENDING;
extern bool FINALE;

bool check_collision( SDL_Rect A, SDL_Rect B );
bool inside_box( int x1, int y1, int x2, int y2, int w2, int h2 );
bool init_music();
void close_music();


#endif  //  _INCLUDES_H