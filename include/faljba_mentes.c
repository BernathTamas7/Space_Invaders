/*#include "debugmalloc.h"
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "fajlba_mentes.h"
#include "strukturak.h"
#include "kirajzol_test.h"


void szoveg_kirajzol(SDL_Renderer*renderer, TTF_Font *font, SDL_Color szin, char *szoveg, int y){
        SDL_Surface *felirat = TTF_RenderUTF8_Solid(font, szoveg, szin);
        SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
        SDL_Rect hova = { (480 - felirat->w) / 2, y, felirat->w, felirat->h };
        SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
        SDL_FreeSurface(felirat);
        SDL_DestroyTexture(felirat_t);
}

void vege_kep(SDL_Renderer* renderer,SDL_Window * window){
    TTF_Font *font = TTF_OpenFont("LiberationSerif-Regular.ttf", 32);
    if (!font) {
        SDL_Log("Nem sikerült betölteni a betûtípust: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return;
    }
    SDL_Color feher = {255,255,255};
    szoveg_kirajzol(renderer,font,feher,"Jatek vege",60);
    SDL_RenderPresent(renderer);

    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT) {}

    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_Quit();
    SDL_Quit();

}*/

