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



void ketjatekos_urhajo_mozgas(SDL_Renderer *renderer,int nehezseg,SDL_Window * window, TTF_Font * font,Allapot*kimenet){
    //életszámlálók
    int p1_elet = 3;
    int p2_elet = 3;
    bool kilep = false;
    Lovedek* ufo_lovedek =  NULL;
    srand(time(NULL));
    int szamlalo = 1;
    int talalat = 0;
    char*kiir = NULL;
    Lovedek * l = NULL;
    Ufo *ufo = NULL;
    egesz_torol(renderer);
    Urhajo p2_hajo = {133, 360, 153, 340};
    Urhajo p1_hajo = {276, 360, 296, 340};
    rectangleRGBA(renderer,p1_hajo.x_1,p1_hajo.y_1,p1_hajo.x_2,p1_hajo.y_2,0,255,0,255);
    rectangleRGBA(renderer,p2_hajo.x_1,p2_hajo.y_1,p2_hajo.x_2,p2_hajo.y_2,0,0,255,255);
    SDL_RenderPresent(renderer);
    bool j_lenyomott = false;
    bool b_lenyomott = false;
    bool a_lenyomott = false;
    bool d_lenyomott = false;
    bool quit = false;
    bool jobbra = true;
    while(!quit){
        SDL_Event event;
        SDL_WaitEvent(&event);

        switch(event.type){
            case SDL_KEYDOWN:
                if(event.key.keysym.sym == SDLK_RIGHT){
                    j_lenyomott = true;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    b_lenyomott = true;
                }
                if(event.key.keysym.sym == SDLK_d){
                    d_lenyomott = true;
                }
                if(event.key.keysym.sym == SDLK_a){
                    a_lenyomott = true;
                }

                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_RIGHT){
                    j_lenyomott = false;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    b_lenyomott = false;
                }
                if(event.key.keysym.sym == SDLK_d){
                    d_lenyomott = false;
                }
                if(event.key.keysym.sym == SDLK_a){
                    a_lenyomott = false;
                }

                if(event.key.keysym.sym == SDLK_m && p1_elet > 0){
                   l = hozzafuz(l,p1_hajo.x_1+7,p1_hajo.y_1-21,p1_hajo.x_2-7,p1_hajo.y_2-6,1);
                }
                if(event.key.keysym.sym == SDLK_v &&p2_elet >0){
                   l = hozzafuz(l,p2_hajo.x_1+7,p2_hajo.y_1-21,p2_hajo.x_2-7,p2_hajo.y_2-6,1);
                }
                break;
            case SDL_USEREVENT:

                if (kiir != NULL) {
                    free(kiir);
                }

                kiir = szovegge(talalat);

                if(j_lenyomott == true && p1_hajo.x_2 <= 440 && p1_elet > 0){
                    mozgat_jobbra(renderer,&p1_hajo);
                }
                if(b_lenyomott == true && p1_hajo.x_1 >= 0 && p1_elet > 0){
                    mozgat_balra(renderer,&p1_hajo);
                }
                if(d_lenyomott == true && p2_hajo.x_2 <= 440 && p2_elet > 0){
                    mozgat_jobbra(renderer,&p2_hajo);
                }
                if(a_lenyomott == true && p2_hajo.x_1 >= 0 && p2_elet > 0){
                    mozgat_balra(renderer,&p2_hajo);
                }



                if(ufo == NULL){
                    ufo = ufo_letrehoz(ufo,5,&jobbra);
                }
                ufo_mozgat(ufo,renderer,&jobbra,nehezseg);

                lovedek_mozgat(renderer,l);

                ufo_lov_mozgat(ufo_lovedek,renderer);

                utkozes(&ufo,&l,renderer,&talalat);

                if(p1_elet > 0){
                    p1_hajokirajzol(renderer,&p1_hajo);
                }

                if(p2_elet > 0){
                    p2_hajokirajzol(renderer,&p2_hajo);
                }

                boxRGBA(renderer,20,20,40,25,0,0,0,255);

                stringRGBA(renderer,20,20,kiir,255,255,255,255);

                lovedek_kirajzol(renderer,l);

                lovedek_kirajzol(renderer,ufo_lovedek);

                ufo_kirajzol(renderer,ufo);

                SDL_RenderPresent(renderer);

                l = lovedek_felszabadit(l);
                //*********************
                szamlalo++;
                if(szamlalo % 100 == 0){
                    int i = 1;
                    if(ufo != NULL){
                        int hanyadik = (rand() % ufo_szam(ufo) + 1);
                        Ufo*iter = ufo;
                        while(iter != NULL && i != hanyadik){
                            iter = iter->kovetkezo;
                            i++;
                        }
                        ufo_lovedek = ufo_lovedek_letrehoz(ufo_lovedek,iter->x_1+7,iter->y_2,iter->x_2-7,iter->y_2+6);
                    }
                }
                //*******************
                eletszamlalo(&p1_hajo,ufo_lovedek,&p1_elet);
                eletszamlalo(&p2_hajo,ufo_lovedek,&p2_elet);
                ufo_lovedek = ufo_lov_felszabadit(ufo_lovedek,&p1_hajo);
                ufo_lovedek = ufo_lov_felszabadit(ufo_lovedek,&p2_hajo);

                if((p1_elet <= 0 && p2_elet <= 0) || kilepo(ufo)){
                    quit = true;
                    kimenet->jatekvege = 1;
                    kimenet->pontszam = talalat;
                }

                break;
            case SDL_QUIT:
                kilep = true;
                if(kilep == true){
                    boxRGBA(renderer,0,0,440,360,0,0,0,255);
                    SDL_RenderPresent(renderer);
                    quit = true;
                    ufo_felszab(ufo);
                    lovedek_egesz_szabadit(l);
                    ossz_ufo_lov_felszabadit(ufo_lovedek);
                    kimenet->jatekos_mod =  0;
                    kimenet->kepernyo = 1;
                    kimenet->nehezseg = 0;
                    if (kiir != NULL) {
                        free(kiir);
                    }
                }
                break;

        }
    }
    printf("%d\n",talalat);
    //printf("%d",elet);
    //SDL_RemoveTimer(idozit);
    if(quit == true && kilep != true){
        ufo_felszab(ufo);
        lovedek_egesz_szabadit(l);
        ossz_ufo_lov_felszabadit(ufo_lovedek);
        if (kiir != NULL) {
                free(kiir);
            }
    }
}

void p1_hajokirajzol(SDL_Renderer * renderer, Urhajo*hajo){
    rectangleRGBA(renderer,hajo->x_1,hajo->y_1,hajo->x_2,hajo->y_2,0,255,0,255);
}

void p2_hajokirajzol(SDL_Renderer * renderer, Urhajo*hajo){
    rectangleRGBA(renderer,hajo->x_1,hajo->y_1,hajo->x_2,hajo->y_2,0,0,255,255);
}


