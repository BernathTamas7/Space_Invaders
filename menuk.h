#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "strukturak.h"
#include "egyjatekos.h"
#include "jatek_vege.h"

void kirajzol(SDL_Renderer *renderer);

int leptetes(SDL_Renderer *renderer,bool*kilepes);

void egesz_torol(SDL_Renderer *renderer);

int nehezseg_valaszto(SDL_Renderer *renderer,Allapot*kimenet);

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font**pfont);

void le_leptetes(int *allapot, int *valasztott, Nyil nyil, SDL_Renderer *renderer);

void fel_leptetes(int *allapot, int *valasztott, Nyil nyil, SDL_Renderer *renderer);

#endif
