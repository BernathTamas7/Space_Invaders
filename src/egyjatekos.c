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

Urhajo urhajo_start(SDL_Renderer *renderer){ // Űrhajó kirajzolásáért felelősfüggvény
    egesz_torol(renderer);
    rectangleRGBA(renderer, 210, 360, 230, 340, 0, 255, 0, 255);
    SDL_RenderPresent(renderer);
    Urhajo uj = {210, 360, 230, 340};
    return uj;
}

char*szovegge(int talalat){ //Pontszámlálót segítő függvény
    char *str = malloc(12);
    if (str == NULL) {
        perror("Memoria hiba");
        exit(1);
    }

    sprintf(str, "%d", talalat);
    return str;
}



void mozgat_jobbra(SDL_Renderer *renderer, Urhajo *hajo){
    boxRGBA(renderer, 0, 360, 440, 340, 0, 0, 0, 255);
    (hajo->x_1)+= 3;
    (hajo->x_2)+= 3;
    rectangleRGBA(renderer, hajo->x_1, hajo->y_1, hajo->x_2, hajo->y_2,0,255,0,255);
    SDL_RenderPresent(renderer);
}

void mozgat_balra(SDL_Renderer *renderer,  Urhajo *hajo){
    boxRGBA(renderer, 0, 360, 440, 340, 0, 0, 0, 255);
    (hajo->x_1)-= 3;
    (hajo->x_2)-= 3;
    rectangleRGBA(renderer, hajo->x_1, hajo->y_1, hajo->x_2, hajo->y_2,0,255,0,255);
    SDL_RenderPresent(renderer);
}

void hajokirajzol(SDL_Renderer * renderer, Urhajo*hajo){//hajót kirajzoló függvény
    rectangleRGBA(renderer,hajo->x_1,hajo->y_1,hajo->x_2,hajo->y_2,0,255,0,255);
}

Uint32 idozit(Uint32 ms, void *param) { //infoc alapján készített időzítő függvény
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}



void urhajo_mozgas(SDL_Renderer *renderer,int nehezseg,SDL_Window * window, TTF_Font * font,Allapot*kimenet){
    //élet megadása
    int elet = 3;
    //Ufó elérte e a játékos szintjét
    bool kilep = false;
    Lovedek* ufo_lovedek =  NULL;
    //random szám generálásához szükséges függvény
    srand(time(NULL));
    int szamlalo = 1;
    int talalat = 0;
    char*kiir = NULL;
    Lovedek * l = NULL;
    Ufo *ufo = NULL;
    urhajo_start(renderer);
    Urhajo hajo = {210, 360, 230, 340};
    bool j_lenyomott = false;
    bool b_lenyomott = false;
    bool quit = false;
    bool jobbra = true;
    while(!quit){ // InfoC alapján
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

                break;
            case SDL_KEYUP:
                if(event.key.keysym.sym == SDLK_RIGHT){
                    j_lenyomott = false;
                }
                if(event.key.keysym.sym == SDLK_LEFT){
                    b_lenyomott = false;
                }

                if(event.key.keysym.sym == SDLK_m){
                   l = hozzafuz(l,hajo.x_1+7,hajo.y_1-21,hajo.x_2-7,hajo.y_2-6,1);
                }
                break;
            case SDL_USEREVENT:

                if (kiir != NULL) {
                    free(kiir);
                }

                kiir = szovegge(talalat);

                if(j_lenyomott == true && hajo.x_2 <= 440){//vizsgálat hogy mozoghat e még jobbra
                    mozgat_jobbra(renderer,&hajo);
                }
                if(b_lenyomott == true && hajo.x_1 >= 0){//vizsgálat hogy mozoghat e még balra
                    mozgat_balra(renderer,&hajo);
                }

                if(ufo == NULL){
                    ufo = ufo_letrehoz(ufo,5,&jobbra);
                }
                ufo_mozgat(ufo,renderer,&jobbra,nehezseg);

                lovedek_mozgat(renderer,l);

                ufo_lov_mozgat(ufo_lovedek,renderer);

                utkozes(&ufo,&l,renderer,&talalat); //ütközés vizsgálata

                hajokirajzol(renderer,&hajo);

                boxRGBA(renderer,20,20,40,25,0,0,0,255);

                stringRGBA(renderer,20,20,kiir,255,255,255,255);

                lovedek_kirajzol(renderer,l);

                lovedek_kirajzol(renderer,ufo_lovedek);

                ufo_kirajzol(renderer,ufo);

                SDL_RenderPresent(renderer);

                l = lovedek_felszabadit(l);
                szamlalo++;
                //random ufo választása
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
                eletszamlalo(&hajo,ufo_lovedek,&elet);
                ufo_lovedek = ufo_lov_felszabadit(ufo_lovedek,&hajo);

                if(elet <= 0 || kilepo(ufo)){
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
    printf("%d",elet);
    if(quit == true && kilep != true){
        ufo_felszab(ufo);
        lovedek_egesz_szabadit(l);
        ossz_ufo_lov_felszabadit(ufo_lovedek);
        if (kiir != NULL) {
            free(kiir);
        }
    }
}




void eletszamlalo(Urhajo*hajo, Lovedek*lovedek,int*elet){
    Lovedek *iter = lovedek;
    while(iter != NULL){
        SDL_Rect lovedek_rect = {iter->x_1,iter->y_1,6,6};
        SDL_Rect hajo_rect = {hajo->x_1,hajo->y_1,20,20};
        SDL_Rect result;
        if(SDL_IntersectRect(&lovedek_rect,&hajo_rect,&result) == SDL_TRUE){
            (*elet)--;
        }
        iter = iter->kovetkezo;
    }
}

Lovedek * hozzafuz(Lovedek * lista, int x1, int y1, int x2, int y2, int irany){
     Lovedek* uj = (Lovedek*)malloc(sizeof(Lovedek));
     if (uj == NULL) {
        printf("Memoriafoglalasi hiba!\n");
        return NULL;
    }
    uj->x_1=x1;
    uj->y_1=y1;
    uj->x_2=x2;
    uj->y_2=y2;
    //uj->irany=1;
    uj->kovetkezo = lista;
    return uj;
}

void ossz_ufo_lov_felszabadit(Lovedek*lovedek){
    Lovedek*iter = lovedek;
    while(iter != NULL){
        Lovedek*uj = iter->kovetkezo;
        free(iter);
        iter = uj;
    }
}

void lovedek_mozgat(SDL_Renderer*renderer, Lovedek * lov){
    Lovedek * aktualis = lov;
    while(aktualis != NULL){
        boxRGBA(renderer, aktualis->x_1, aktualis->y_1, aktualis->x_2, aktualis->y_2, 0, 0, 0, 255);
        aktualis->y_1 -= 6;
        aktualis->y_2 -= 6;
        aktualis = aktualis->kovetkezo;

    }
}

Lovedek* lovedek_felszabadit(Lovedek*lista){
    Lovedek * mozgo = lista;
    Lovedek *lemarado = NULL;
    while(mozgo != NULL){
        if(mozgo->kovetkezo==NULL&&mozgo->y_2<=0&&lemarado ==NULL){
            free(mozgo);
            return NULL;
        }
        else{
            if(lemarado == NULL&&mozgo->kovetkezo!=NULL&&mozgo->y_2<=0){
                lista = mozgo->kovetkezo;
                free(mozgo);
                mozgo=lista;
            }
            else if(mozgo->y_2<=0&&lemarado!=NULL){
                lemarado->kovetkezo = mozgo->kovetkezo;
                free(mozgo);
                mozgo = lemarado->kovetkezo;
            }
            else{
                lemarado = mozgo;
                mozgo = mozgo->kovetkezo;
            }
        }
    }
    return lista;
}




Lovedek * ufo_lov_felszabadit(Lovedek*lovedek,Urhajo*hajo){
    Lovedek *iter = lovedek;
    Lovedek* elozo = NULL;
    while(iter != NULL){
        SDL_Rect lovedek_rect = {iter->x_1,iter->y_1,6,6};
        SDL_Rect hajo_rect = {hajo->x_1,hajo->y_1,20,20};
        SDL_Rect result;
        if(iter->y_2>360 || SDL_IntersectRect(&lovedek_rect,&hajo_rect,&result) == SDL_TRUE){
            Lovedek*kov = iter->kovetkezo;
                if (elozo == NULL) {
                    lovedek = kov;
                }
                else {
                    elozo->kovetkezo = kov;
                }
                free(iter);
                iter = kov;
            }
            else {
                elozo = iter;
                iter = iter->kovetkezo;
            }
        }
        return lovedek;
    }


void ufo_lov_mozgat(Lovedek*lovedek,SDL_Renderer*renderer){
    Lovedek*iter = lovedek;
    while(iter != NULL){
        boxRGBA(renderer, iter->x_1, iter->y_1, iter->x_2, iter->y_2, 0, 0, 0, 255);
        iter->y_1 += 6;
        iter->y_2 += 6;
        iter = iter->kovetkezo;
    }
}

Lovedek*ufo_lovedek_letrehoz(Lovedek*lovedek,int x1,int y1, int x2, int y2){
    Lovedek*uj=(Lovedek*)malloc(sizeof(Lovedek));
    if(uj == NULL){
        printf("Memoriahiba");
    }
    uj->x_1=x1;
    uj->y_1=y1;
    uj->x_2=x2;
    uj->y_2=y2;
    //uj->irany = 1;
    uj->kovetkezo = lovedek;
    return uj;
}

Ufo * ufo_letrehoz(Ufo*fej,int sorszam, bool * jobbra){
    int y_lyuk = 0;
    for(int j = 0; j < 1+sorszam;j++){
        int x_lyuk = 0;
        for(int i = 0; i<3;i++){
            Ufo * uj = (Ufo*)malloc(sizeof(Ufo));
            if(uj == NULL){
                printf("Memoria hiba");
                return fej;
            }
            uj->x_1 =i*20+20+x_lyuk;
            uj->y_1 = (j*20)+y_lyuk;
            uj->x_2 = i*20+40+x_lyuk;
            uj->y_2 = 20 + (j * 20)+y_lyuk;
            uj->kovetkezo = fej;
            fej = uj;
            x_lyuk+=15;
        }
    y_lyuk+=7;
    }
    *jobbra = true;
    return fej;
}

void ufo_mozgat(Ufo*fej,SDL_Renderer * renderer, bool * jobbra,int nehezseg){
    bool irany_valtas = false;
    Ufo * mozgo = fej;
    while(mozgo!=0 && !irany_valtas){
        if(mozgo->x_2>=400){
            irany_valtas = true;
        }
        else if(mozgo->x_1<=10){
            irany_valtas = true;
        }
        mozgo = mozgo->kovetkezo;
    }
    if(irany_valtas){
        mozgo = fej;
        while(mozgo != NULL){
            lefelemozgat(mozgo,renderer);
            mozgo = mozgo->kovetkezo;
        }
        *jobbra = !(*jobbra);
    }
        mozgo = fej;
        while(mozgo != NULL){
            if(*jobbra){
                jobbramozgat(mozgo,renderer,nehezseg);
            }
            else{
                balramozgat(mozgo,renderer,nehezseg);
            }
            mozgo = mozgo->kovetkezo;
        }

}

void lefelemozgat(Ufo*ptr, SDL_Renderer*renderer){
        rectangleRGBA(renderer, ptr->x_1, ptr->y_1, ptr->x_2, ptr->y_2, 0, 0, 0, 255);
        ptr->y_1 += 40;
        ptr->y_2 += 40;
        rectangleRGBA(renderer, ptr->x_1, ptr->y_1, ptr->x_2, ptr->y_2, 255, 0, 0, 255);
}

void jobbramozgat(Ufo*ptr, SDL_Renderer*renderer,int nehezseg){
        rectangleRGBA(renderer, ptr->x_1, ptr->y_1, ptr->x_2, ptr->y_2, 0, 0, 0, 255);
        ptr->x_1 += nehezseg;
        ptr->x_2 += nehezseg;
        rectangleRGBA(renderer, ptr->x_1, ptr->y_1, ptr->x_2, ptr->y_2, 255, 0, 0, 255);
}

void balramozgat(Ufo*ptr, SDL_Renderer*renderer,int nehezseg){
        rectangleRGBA(renderer, ptr->x_1, ptr->y_1, ptr->x_2, ptr->y_2, 0, 0, 0, 255);
        ptr->x_1 -= nehezseg;
        ptr->x_2 -= nehezseg;
        rectangleRGBA(renderer, ptr->x_1, ptr->y_1, ptr->x_2, ptr->y_2, 255, 0, 0, 255);
}

void utkozes(Ufo**ufo, Lovedek**lovedek, SDL_Renderer * renderer,int*talalat_szam){
    Lovedek* l_iter = *lovedek;
    while(l_iter != NULL){
        Lovedek*l_temp =  l_iter->kovetkezo;
        Ufo*u_iter = *ufo;
        while(u_iter != NULL){
            SDL_Rect lovedek_rect = {l_iter->x_1,l_iter->y_1,6,6};
            SDL_Rect ufo_rect = {u_iter->x_1,u_iter->y_1,20,20};
            SDL_Rect result;
            Ufo*u_temp =  u_iter->kovetkezo;

            if(SDL_IntersectRect(&lovedek_rect,&ufo_rect,&result) == SDL_TRUE){
                (*talalat_szam)++;
                boxRGBA(renderer,0,0,440,360,0,0,0,255);
                *ufo = ufo_elem_torles(*ufo,u_iter);
                *lovedek = lovedek_elem_torles(*lovedek,l_iter);

            }
            u_iter = u_temp;
        }
        l_iter = l_temp;
    }
}

Ufo* ufo_elem_torles(Ufo*eleje,Ufo* torol){
    Ufo *lemarado = NULL;
    Ufo *mozgo = eleje;

    while (mozgo != NULL && !(mozgo->y_1 == torol->y_1 && mozgo->x_1 == torol->x_1)) {
        lemarado = mozgo;
        mozgo = mozgo->kovetkezo;
    }
    Ufo*ujeleje = NULL;

/* megtalált elem törlése */
    if (mozgo == NULL) {
    }
    else if (lemarado == NULL) { /* az elsõ elemet kell törölni */
        ujeleje = mozgo->kovetkezo;

        free(mozgo);
    } else {                       /* a közepérõl/végérõl törlünk */
        lemarado->kovetkezo = mozgo->kovetkezo;
        free(mozgo);
        ujeleje = eleje;
    }
    return ujeleje;
}

Lovedek* lovedek_elem_torles(Lovedek*eleje,Lovedek* torol){
    Lovedek *lemarado = NULL;
    Lovedek *mozgo = eleje;
    while (mozgo != NULL && !(mozgo->x_1 == torol->x_1 && mozgo->y_1 == torol->y_1)) {
        lemarado = mozgo;
        mozgo = mozgo->kovetkezo;
    }

    Lovedek *ujeleje = NULL;
/* megtalált elem törlése */
    if (mozgo == NULL) {
    }
    else if (lemarado == NULL) { /* az elsõ elemet kell törölni */
        ujeleje = mozgo->kovetkezo;
        free(mozgo);
    } else {                       /* a közepérõl/végérõl törlünk */
        lemarado->kovetkezo = mozgo->kovetkezo;
        free(mozgo);
        ujeleje = eleje;
    }

    return ujeleje;
}

void lovedek_kirajzol(SDL_Renderer * renderer, Lovedek * eleje){
    Lovedek* iter = eleje;
    while(iter != NULL){
        rectangleRGBA(renderer,iter->x_1,iter->y_1,iter->x_2,iter->y_2,0,0,255,255);
        iter = iter->kovetkezo;
    }
}

bool kilepo(Ufo*ufo){
    Ufo* iter = ufo;
    while(iter != 0){
        if(iter->y_2 > 340){
            return true;
        }
        iter = iter->kovetkezo;
    }
    return false;
}

void ufo_felszab(Ufo*ufo){
    Ufo*iter = ufo;
    while(iter != NULL){
        Ufo*uj = iter->kovetkezo;
        free(iter);
        iter = uj;
    }
}

void lovedek_egesz_szabadit(Lovedek*lov){
    Lovedek*iter = lov;
    while(iter != NULL){
        Lovedek*uj = iter->kovetkezo;
        free(iter);
        iter = uj;
    }
}

int ufo_szam(Ufo*ufo){
    int darab = 0;
    Ufo*iter = ufo;
    while(iter != NULL){
        darab++;
        iter = iter->kovetkezo;
    }
    return darab;
}

void ufo_kirajzol(SDL_Renderer * renderer, Ufo * eleje){
    Ufo* iter = eleje;
    while(iter != NULL){
        rectangleRGBA(renderer,iter->x_1,iter->y_1,iter->x_2,iter->y_2,255,0,0,255);
        iter = iter->kovetkezo;
    }
}
