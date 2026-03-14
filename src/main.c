#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <SDL_ttf.h>
#include "fajlba_mentes.h"
#include "strukturak.h"
#include "menuk.h"
#include "debugmalloc.h"
#include "jatek_vege.h"
#include "Scoreboard.h"
#include "szovegbevitel.h"

int main(int argc, char *argv[]) {
    //paraméterek megadása, változók létrehozása
    const int ablak_szeles = 440;
    const int ablak_magas =  360;
    SDL_Window *window;
    TTF_Font * font;
    SDL_Renderer *renderer;

    SDL_Color hatter = {255, 255, 255, 255};
    SDL_Color szoveg = {0, 0, 0, 255};
    SDL_Rect teglalap = {50, 50, 400, 50};
    char bemenet[256] = {0};
    sdl_init("Jatek", ablak_szeles, ablak_magas, &window, &renderer,&font);
    SDL_TimerID id = SDL_AddTimer(30, idozit, NULL); // InfoC függvény


     Allapot kimenet = {1,0,0,0,0}; // Alapállapot beállítása
     bool quit = false;
     while(!quit){
        //főmenü megjelenítése
        if(kimenet.kepernyo == 1 && kimenet.jatekos_mod == 0 && kimenet.nehezseg == 0){
            kirajzol(renderer);
            int seged = leptetes(renderer,&quit);
            if(seged == 0){
                kimenet.kepernyo = 2;
                kimenet.jatekos_mod = 1;
            }
            else if(seged == 1){
                kimenet.kepernyo = 2;
                kimenet.jatekos_mod = 2;
            }
            else if(seged == 2){
                kimenet.kepernyo = 4;
            }
        }
        //Scoreboard megjelenítése
        else if(kimenet.kepernyo == 4){
            int seged = dicsosegtabla(renderer,&kimenet);
            if(seged == 0 && kimenet.kepernyo != 1){
                megnyitas("1pkonnyu.txt",renderer,&kimenet);
            }
            if(seged == 1 && kimenet.kepernyo != 1){
                megnyitas("1pkozepes.txt",renderer,&kimenet);
            }
            if(seged == 2 && kimenet.kepernyo != 1){
                megnyitas("1pnehez.txt",renderer,&kimenet);
            }
            if(seged == 3 && kimenet.kepernyo != 1){
                megnyitas("2pkonnyu.txt",renderer,&kimenet);
            }
            if(seged == 4 && kimenet.kepernyo != 1){
                megnyitas("2pkozepes.txt",renderer,&kimenet);
            }
            if(seged == 5 && kimenet.kepernyo != 1){
                megnyitas("2pnehez.txt",renderer,&kimenet);
            }
            if(seged == 6 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 1;
                kimenet.jatekos_mod = 0;
                kimenet.nehezseg = 0;
            }
        }
        //Nehézségválasztó megjelenítése
        else if(kimenet.kepernyo == 2 && kimenet.jatekos_mod == 1 && kimenet.nehezseg == 0){
            int seged = nehezseg_valaszto(renderer,&kimenet);
            if(seged == 0 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 3;
                kimenet.jatekos_mod = 1;
                kimenet.nehezseg = 1;
            }
            if(seged == 1 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 3;
                kimenet.jatekos_mod = 1;
                kimenet.nehezseg = 2;
            }
            if(seged == 2 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 3;
                kimenet.jatekos_mod = 1;
                kimenet.nehezseg = 3;
            }
            if(seged == 3 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 1;
                kimenet.jatekos_mod = 0;
                kimenet.nehezseg = 0;
            }
        }
        //nehézségválasztó megjelenítése
        else if(kimenet.kepernyo == 2 && kimenet.jatekos_mod == 2 && kimenet.nehezseg == 0){
            int seged = nehezseg_valaszto(renderer,&kimenet);
            if(seged == 0 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 3;
                kimenet.jatekos_mod = 2;
                kimenet.nehezseg = 1;
            }
            if(seged == 1 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 3;
                kimenet.jatekos_mod = 2;
                kimenet.nehezseg = 2;
            }
            if(seged == 2 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 3;
                kimenet.jatekos_mod = 2;
                kimenet.nehezseg = 3;
            }
            if(seged == 3 && kimenet.kepernyo != 1){
                kimenet.kepernyo = 1;
                kimenet.jatekos_mod = 0;
                kimenet.nehezseg = 0;
            }
        }
        //egyjátékos mód futtatása
        else if(kimenet.kepernyo == 3 && kimenet.jatekos_mod == 1 && kimenet.jatekvege == 0){
            if(kimenet.nehezseg == 1){
                urhajo_mozgas(renderer,2,window,font,&kimenet);
            }
            else if(kimenet.nehezseg == 2){
                urhajo_mozgas(renderer,5,window,font,&kimenet);
            }
            else if(kimenet.nehezseg == 3){
                urhajo_mozgas(renderer,7,window,font,&kimenet);
            }

        }
        //kétjátékos mód futtatása
        else if(kimenet.kepernyo == 3 && kimenet.jatekos_mod == 2 && kimenet.jatekvege == 0){
            if(kimenet.nehezseg == 1){
                ketjatekos_urhajo_mozgas(renderer,2,window,font,&kimenet);
            }
            else if(kimenet.nehezseg == 2){
                ketjatekos_urhajo_mozgas(renderer,5,window,font,&kimenet);
            }
            else if(kimenet.nehezseg == 3){
                ketjatekos_urhajo_mozgas(renderer,7,window,font,&kimenet);
            }
        }
        //játék végének kezelése
        else if(kimenet.jatekvege == 1){
            int seged = jatek_vege(renderer,&kimenet);
            //játék újra azonos beállításokkal
            if(seged == 0){
                kimenet.jatekvege = 0;
            }
            //eredmény fájlba mentése
            else if(seged == 1){
                if(kimenet.jatekos_mod == 1 && kimenet.nehezseg == 1){
                    if (input_text(bemenet, sizeof(bemenet), teglalap, hatter, szoveg, font, renderer)) {
                        printf("Bevitt adat: %s\n", bemenet);
                        mentes_fajlba(bemenet,kimenet.pontszam, "1pkonnyu.txt"); // Adatok mentése fájlba
                        memset(bemenet, 0, sizeof(bemenet)); // Bemenet törlése
                    }
                }
                else if(kimenet.jatekos_mod == 1 && kimenet.nehezseg == 2){
                    if (input_text(bemenet, sizeof(bemenet), teglalap, hatter, szoveg, font, renderer)) {
                        printf("Bevitt adat: %s\n", bemenet);
                        mentes_fajlba(bemenet,kimenet.pontszam, "1pkozepes.txt"); // Adatok mentése fájlba
                        memset(bemenet, 0, sizeof(bemenet)); // Bemenet törlése
                    }
                }
                else if(kimenet.jatekos_mod == 1 && kimenet.nehezseg == 3){
                    if (input_text(bemenet, sizeof(bemenet), teglalap, hatter, szoveg, font, renderer)) {
                        printf("Bevitt adat: %s\n", bemenet);
                        mentes_fajlba(bemenet,kimenet.pontszam, "1pnehez.txt"); // Adatok mentése fájlba
                        memset(bemenet, 0, sizeof(bemenet)); // Bemenet törlése
                    }
                }
                else if(kimenet.jatekos_mod == 2 && kimenet.nehezseg == 1){
                    if (input_text(bemenet, sizeof(bemenet), teglalap, hatter, szoveg, font, renderer)) {
                        printf("Bevitt adat: %s\n", bemenet);
                        mentes_fajlba(bemenet,kimenet.pontszam, "2pkonnyu.txt"); // Adatok mentése fájlba
                        memset(bemenet, 0, sizeof(bemenet)); // Bemenet törlése
                    }
                }
                else if(kimenet.jatekos_mod == 2 && kimenet.nehezseg == 2){
                    if (input_text(bemenet, sizeof(bemenet), teglalap, hatter, szoveg, font, renderer)) {
                        printf("Bevitt adat: %s\n", bemenet);
                        mentes_fajlba(bemenet,kimenet.pontszam, "2pkozepes.txt"); // Adatok mentése fájlba
                        memset(bemenet, 0, sizeof(bemenet)); // Bemenet törlése
                    }
                }
                else if(kimenet.jatekos_mod == 2 && kimenet.nehezseg == 3){
                    if (input_text(bemenet, sizeof(bemenet), teglalap, hatter, szoveg, font, renderer)) {
                        printf("Bevitt adat: %s\n", bemenet);
                        mentes_fajlba(bemenet,kimenet.pontszam, "2pnehez.txt"); // Adatok mentése fájlba
                        memset(bemenet, 0, sizeof(bemenet)); // Bemenet törlése
                    }
                }
                egesz_torol(renderer);
                kimenet.jatekos_mod = 0;
                kimenet.jatekvege = 0;
                kimenet.kepernyo = 1;
                kimenet.nehezseg = 0;
            }
            //főmenübe lépés
            else if(seged == 2){
                kimenet.kepernyo = 1;
                kimenet.jatekos_mod = 0;
                kimenet.jatekvege = 0;
                kimenet.nehezseg = 0;
            }
        }
     }
    SDL_RemoveTimer(id);
    return 0;
}



