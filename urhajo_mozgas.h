#ifndef URHAJO_H_INCLUDED
#define URHAJO_H_INCLUDED

#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "jatek_vege.h"
#include "strukturak.h"
#include "menuk.h"

Urhajo urhajo_start(SDL_Renderer * renderer);

void urhajo_mozgas(SDL_Renderer *renderer,int nehezseg,SDL_Window * window,TTF_Font*font,Allapot*kimenet);

void mozgat_jobbra(SDL_Renderer *renderer, Urhajo *hajo);

void mozgat_balra(SDL_Renderer *renderer,  Urhajo *hajo);

Uint32 idozit(Uint32 ms, void *param);

char*szovegge(int talalat);

//******************-innentol mar lovedek

Lovedek * hozzafuz(Lovedek*lista,int x1, int y1, int x2, int y2, int irany);

void lovedek_mozgat(SDL_Renderer*render, Lovedek * lov);

Lovedek* lovedek_felszabadit(Lovedek*lista);

Ufo * ufo_letrehoz(Ufo*fej,int sorszam, bool * jobbra);

void utkozes(Ufo**ufo, Lovedek**lovedek, SDL_Renderer * renderer, int*talalat_szam);

Ufo* ufo_elem_torles(Ufo*eleje,Ufo* torol);

Lovedek* lovedek_elem_torles(Lovedek*eleje,Lovedek* torol);

void hajokirajzol(SDL_Renderer * renderer, Urhajo*hajo);

Lovedek* lovedek_elem_torles(Lovedek*eleje,Lovedek* torol);

bool kilepo(Ufo*ufo);

void ufo_felszab(Ufo*ufo);

void lovedek_egesz_szabadit(Lovedek*lov);

int ufo_szam(Ufo*ufo);

Lovedek*ufo_lovedek_letrehoz(Lovedek*lovedek,int x1,int y1, int x2, int y2);

void ufo_lov_mozgat(Lovedek*lovedek,SDL_Renderer*renderer);

Lovedek * ufo_lov_felszabadit(Lovedek*lovedek,Urhajo*hajo);

Lovedek * hozzafuz(Lovedek * lista, int x1, int y1, int x2, int y2, int irany);

void eletszamlalo(Urhajo*hajo, Lovedek*lovedek,int*elet);

void balramozgat(Ufo*ptr, SDL_Renderer*renderer,int nehezseg);

void jobbramozgat(Ufo*ptr, SDL_Renderer*renderer,int nehezseg);

void ufo_mozgat(Ufo*fej,SDL_Renderer * renderer, bool * jobbra,int nehezseg);

void lovedek_kirajzol(SDL_Renderer * renderer, Lovedek * eleje);

void ufo_kirajzol(SDL_Renderer * renderer, Ufo * eleje);

void ossz_ufo_lov_felszabadit(Lovedek*lovedek);

void lefelemozgat(Ufo*ptr, SDL_Renderer*renderer);
#endif
