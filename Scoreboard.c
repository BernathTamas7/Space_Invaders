#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include "strukturak.h"
#include "menuk.h"
#include "jatek_vege.h"
#include "egyjatekos.h"
#include "debugmalloc.h"
#include "ketjatekos.h"
#include "Scoreboard.h"

int dicsosegtabla(SDL_Renderer * renderer, Allapot*kimenet){
    bool quit = false;
    bool enter = false;
    egesz_torol(renderer);
    stringRGBA(renderer,250,75,"1pkonnyu.txt",255,255,255,255);
    stringRGBA(renderer,250,100,"1pkozepes.txt",255,255,255,255);
    stringRGBA(renderer,250,125,"1pnehez.txt",255,255,255,255);
    stringRGBA(renderer,250,150,"2pkonnyu.txt",255,255,255,255);
    stringRGBA(renderer,250,175,"2pkozepes",255,255,255,255);
    stringRGBA(renderer,250,200,"2pnehez.txt",255,255,255,255);
    stringRGBA(renderer,250,225,"Vissza",255,255,255,255);
    thickLineRGBA(renderer, 100, 75, 140, 75, 2, 255, 255, 255, 255);
    trigonRGBA(renderer,140,60,140,90,170,75,255,255,255,255);
    Nyil valaszt = {100, 75, 140, 75, 140,60,140,90,170,75};
    SDL_RenderPresent(renderer);
        int valasztott = 0;
        int allapot = 0;
        while (!quit && !enter) {
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch (event.type) {

            case SDL_KEYDOWN:

                if(event.key.keysym.sym == SDLK_DOWN && valasztott != 6){
                    boxRGBA(renderer,100,60,170,240,0,0,0,255);
                    le_leptetes(&allapot,&valasztott,valaszt,renderer);
                }
                if(event.key.keysym.sym == SDLK_UP && valasztott != 0){
                    boxRGBA(renderer,100,60,170,240,0,0,0,255);
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

void megnyitas(char*nev,SDL_Renderer*renderer,Allapot*kimenet){
   /* FILE *file = fopen(nev, "r");
    if (file == NULL) {
        perror("Fajl megnyitasa sikertelen");
        return;
    }
    char szoveg[21];
    int szam;
    int y = 50;
    int darab = 0;
    int max_elem = 10;
    while (darab < max_elem && fscanf(file, "%20[^_]_%d\n", szoveg, &szam) == 2) {
        char egesz[50];
        snprintf(egesz, sizeof(egesz), "%s_%d", szoveg, szam);
        stringRGBA(renderer, 50, y, egesz, 255, 255, 255, 255);
        darab++;
        y+= 25;
    }
    SDL_RenderPresent(renderer);
    fclose(file);

    bool quit = false;
    while(!quit){
        SDL_Event  ev;
        SDL_WaitEvent(&ev);
        if(ev.type == SDL_QUIT){
            quit = true;
            kimenet->jatekos_mod = 0;
            kimenet->kepernyo = 1;
            kimenet->nehezseg = 0;
            egesz_torol(renderer);
        }
    }
*/
  FILE *file = fopen(nev, "r");
    if (file == NULL) {
        perror("Fájl megnyitása sikertelen");
        return;
    }

    char szovegek[100][21]; // Maximum 100 szöveg tárolására
    int pontszamok[100];
    int darab = 0;

    // Adatok beolvasása
    while (darab < 100 && fscanf(file, "%20[^_]_%d\n", szovegek[darab], &pontszamok[darab]) == 2) {
        darab++;
    }
    fclose(file);

    // Sorba rendezés pontszám szerint csökkenõ sorrendben (egyszerû buborékos rendezés)
    for (int i = 0; i < darab - 1; i++) {
        for (int j = i + 1; j < darab; j++) {
            if (pontszamok[i] < pontszamok[j]) {
                // Pontszámok cseréje
                int temp_pont = pontszamok[i];
                pontszamok[i] = pontszamok[j];
                pontszamok[j] = temp_pont;

                // Szövegek cseréje
                char temp_szoveg[21];
                strcpy(temp_szoveg, szovegek[i]);
                strcpy(szovegek[i], szovegek[j]);
                strcpy(szovegek[j], temp_szoveg);
            }
        }
    }

    // Kirajzolás, maximum 10 adat megjelenítése
    int max_megjelenitett = darab < 10 ? darab : 10;
    int y = 50;
    for (int i = 0; i < max_megjelenitett; i++) {
        char egesz[50];
        snprintf(egesz, sizeof(egesz), "%s_%d", szovegek[i], pontszamok[i]);
        stringRGBA(renderer, 50, y, egesz, 255, 255, 255, 255);
        y += 25;
    }

    SDL_RenderPresent(renderer);

    // Eseménykezelés
    bool quit = false;
    while (!quit) {
        SDL_Event ev;
        SDL_WaitEvent(&ev);
        if (ev.type == SDL_QUIT) {
            quit = true;
            kimenet->jatekos_mod = 0;
            kimenet->kepernyo = 1;
            kimenet->nehezseg = 0;
            egesz_torol(renderer);
        }
    }
}
