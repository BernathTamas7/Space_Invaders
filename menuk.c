#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include "strukturak.h"
#include "menuk.h"
#include "fajlba_mentes.h"
#include "jatek_vege.h"
#include "egyjatekos.h"
#include "debugmalloc.h"

// SDL_init****************************

void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer,TTF_Font**pfont) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }


    TTF_Init();
    TTF_Font *font = TTF_OpenFont("LiberationSerif-Regular.ttf", 32);
    if (font == NULL) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, szeles, magas, 0);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
    *pfont = font;
}

// Ablak kirajzolasa************************

void kirajzol(SDL_Renderer *renderer){
    stringRGBA(renderer,15,15,"Menu",255,255,255,255);
    stringRGBA(renderer,250,110,"1 Player",255,255,255,255);
    stringRGBA(renderer,250,135,"2 Player",255,255,255,255);
    stringRGBA(renderer,250,160,"Scoreboard",255,255,255,255);
    thickLineRGBA(renderer, 100, 110, 140, 110, 2, 255, 255, 255, 255);
    trigonRGBA(renderer,140,95,140,125,170,110,255,255,255,255);
    SDL_RenderPresent(renderer);
}
//************************************

void le_leptetes(int *allapot, int *valasztott, Nyil nyil, SDL_Renderer *renderer){
    (*valasztott)++;
    *allapot+=25;
    boxRGBA(renderer,100,95,170,200,0,0,0,255);
    thickLineRGBA(renderer,nyil.vonal_x1,nyil.vonal_y1+*allapot, nyil.vonal_x2, nyil.vonal_y2+*allapot, 2, 255, 255, 255, 255);
    trigonRGBA(renderer,nyil.harom_x1,nyil.harom_y1+*allapot,nyil.harom_x2,nyil.harom_y2+*allapot,nyil.harom_x3,nyil.harom_y3+*allapot,255,255,255,255);
    SDL_RenderPresent(renderer);
}

void fel_leptetes(int *allapot, int *valasztott, Nyil nyil, SDL_Renderer *renderer){
    (*valasztott)--;
    *allapot-=25;
    boxRGBA(renderer,100,95,170,200,0,0,0,255);
    thickLineRGBA(renderer,nyil.vonal_x1,nyil.vonal_y1+*allapot, nyil.vonal_x2, nyil.vonal_y2+*allapot, 2, 255, 255, 255, 255);
    trigonRGBA(renderer,nyil.harom_x1,nyil.harom_y1+*allapot,nyil.harom_x2,nyil.harom_y2+*allapot,nyil.harom_x3,nyil.harom_y3+*allapot,255,255,255,255);
    SDL_RenderPresent(renderer);
}

void egesz_torol(SDL_Renderer *renderer){
    boxRGBA(renderer, 0, 0, 440, 360, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}

int leptetes(SDL_Renderer *renderer,bool *kilep){
    Nyil valaszt = {100, 110, 140, 110, 140, 95, 140, 125, 170, 110};
    bool quit = false;
    bool enter = false;
    int valasztott = 0;
    int allapot = 0;
    kirajzol(renderer);
    while (!quit && !enter) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_DOWN && valasztott != 2){
                    le_leptetes(&allapot,&valasztott,valaszt,renderer);
                    }
                if(event.key.keysym.sym == SDLK_UP && valasztott != 0){
                    fel_leptetes(&allapot,&valasztott,valaszt,renderer);
                   }
                if(event.key.keysym.sym == SDLK_SPACE){
                    boxRGBA(renderer,0,0,440,360,0,0,0,255);
                    enter = true;
                    return valasztott;
                }
                break;

            case SDL_QUIT:
                quit = true;
                *kilep = true;
                break;
        }

            SDL_RenderPresent(renderer);
    }
    return valasztott;
}

// nehezseg valsztas******************

int nehezseg_valaszto(SDL_Renderer *renderer,Allapot*kimenet){
    bool quit = false;
    bool enter = false;

        egesz_torol(renderer);
        Nyil valaszt = {100, 110, 140, 110, 140, 95, 140, 125, 170, 110};
        stringRGBA(renderer,15,15,"Difficulty",255,255,255,255);
        stringRGBA(renderer,250,110,"Konnyu",255,255,255,255);
        stringRGBA(renderer,250,135,"Kozepes",255,255,255,255);
        stringRGBA(renderer,250,160,"Nehez",255,255,255,255);
        stringRGBA(renderer,250,185,"Vissza",255,255,255,255);
        thickLineRGBA(renderer, 100, 110, 140, 110, 2, 255, 255, 255, 255);
        trigonRGBA(renderer,140,95,140,125,170,110,255,255,255,255);
        SDL_RenderPresent(renderer);
        int valasztott = 0;
        int allapot = 0;
        while (!quit && !enter) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {

            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_DOWN && valasztott != 3){
                    le_leptetes(&allapot,&valasztott,valaszt,renderer);
                    }
                if(event.key.keysym.sym == SDLK_UP && valasztott != 0){
                    fel_leptetes(&allapot,&valasztott,valaszt,renderer);
                }
                if(event.key.keysym.sym == SDLK_SPACE){
                    boxRGBA(renderer,0,0,440,360,0,0,0,255);
                    enter = true;
                    return valasztott;
                }
                break;

            case SDL_QUIT:
                quit = true;
                boxRGBA(renderer,0,0,440,360,0,0,0,255);
                SDL_RenderPresent(renderer);
                kimenet->kepernyo = 1;
                kimenet->jatekos_mod = 0;
                kimenet->nehezseg = 0;
                break;
        }

            SDL_RenderPresent(renderer);
    }

    return valasztott;
}




