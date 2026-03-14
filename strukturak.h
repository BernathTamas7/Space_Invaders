#ifndef STRUKTURAK_H_INCLUDED
#define STRUKTURAK_H_INCLUDED

typedef struct Nyil{
        int vonal_x1,
        vonal_y1,
        vonal_x2,
        vonal_y2,
        harom_x1,
        harom_y1,
        harom_x2,
        harom_y2,
        harom_x3,
        harom_y3;
    } Nyil;

typedef struct Urhajo{
        int x_1,
            y_1,
            x_2,
            y_2;
    } Urhajo;

typedef struct Lovedek{
    int x_1,
        y_1,
        x_2,
        y_2;
    struct Lovedek * kovetkezo;
} Lovedek;

typedef struct Ufo{
        int x_1,
            y_1,
            x_2,
            y_2;
        struct Ufo*kovetkezo;
    } Ufo;

typedef struct Allapot{
    int kepernyo;
    int jatekos_mod;
    int nehezseg;
    int jatekvege;
    int pontszam;
}  Allapot;


#endif
