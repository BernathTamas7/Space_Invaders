#ifndef SCOREBOARD_H_INCLUDED
#define SCOREBOARD_H_INCLUDED

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
#include "ketjatekos.h"

int dicsosegtabla(SDL_Renderer * renderer, Allapot*kimenet);

void megnyitas(char*nev,SDL_Renderer*renderer,Allapot*kimenet);

#endif
