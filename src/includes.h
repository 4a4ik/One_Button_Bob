#ifndef _INCLUDES_H
#define _INCLUDES_H

#define TILE_WIDTH 32
#define TILE_HEIGHT 32
#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#include<SDL.h>
#include<SDL_image.h>
#include<stdio.h>
#include<iostream>
#include<vector>
#include<string>
#include<map>

bool check_collision( SDL_Rect A, SDL_Rect B );


#endif  //  _INCLUDES_H