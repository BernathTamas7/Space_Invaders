#include "debugmalloc.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "fajlba_mentes.h"
#include "strukturak.h"
#include "menuk.h"
#include "jatek_vege.h"


int jatek_vege(SDL_Renderer*renderer,Allapot*kimenet){ // menü megjelenítése
    bool quit = false;
    bool enter = false;

        Nyil valaszt = {100, 135, 140, 135, 140, 120, 140, 150, 170, 135};
        stringRGBA(renderer,220,100,"Jatek vege",255,255,255,255);
        stringRGBA(renderer,250,135,"ujra",255,255,255,255);
        stringRGBA(renderer,250,160,"ment",255,255,255,255);
        stringRGBA(renderer,250,185,"menu",255,255,255,255);
        thickLineRGBA(renderer, 100, 135, 140, 135, 2, 255, 255, 255, 255);
        trigonRGBA(renderer,140,120,140,150,170,135,255,255,255,255);
        SDL_RenderPresent(renderer);
        int valasztott = 0;
        int allapot = 0;
        while (!quit && !enter) { // InfoC felépítés alapján
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

