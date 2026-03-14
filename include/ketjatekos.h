#ifndef KETJATEKOS_H_INCLUDED
#define KETJATEKOS_H_INCLUDED

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jatek_vege.h"
#include "strukturak.h"
#include "menuk.h"
#include "egyjatekos.h"

void ketjatekos_urhajo_mozgas(SDL_Renderer *renderer,int nehezseg,SDL_Window * window, TTF_Font * font,Allapot*kimenet);

void p1_hajokirajzol(SDL_Renderer * renderer, Urhajo*hajo);

void p2_hajokirajzol(SDL_Renderer * renderer, Urhajo*hajo);

#endif
