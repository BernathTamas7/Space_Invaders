#ifndef SZOVEGBEVITEL__INCLUDED
#define SZOVEGBEVITEL__INCLUDED

#include <SDL2_gfxPrimitives.h>
#include <SDL.h>
#include <SDL_ttf.h>

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#include "jatek_vege.h"
#include "strukturak.h"
#include "menuk.h"
#include "egyjatekos.h"

bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);

void fajlba_ment(const char *fajlnev, const char *szoveg);

bool szovegbevitel_fajlba(const char *fajlnev, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);

//void mentes_fajlba(const char *bemenet, const char *fajlnev);
void mentes_fajlba(const char *nev, int pontszam, const char *fajlnev);
#endif
