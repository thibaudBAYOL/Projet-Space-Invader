
#ifndef thibaudSasi_0_f
#define thibaudSasi_0_f


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
       #include <unistd.h> // terminos
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h> // open


typedef struct Vaisseau Vaisseau;
typedef struct Type Type;


struct Type{
    int vit;// vitesse du tire en case / seconde
    double cad;// cadence de tire ex: 0.5
    char tir;// apparence du tire
    int deg;// 			les degats engendre
    int vie;// vie par defaut

    int lcycle;
    int** cycle;
    
    int h;// nb de case en hauteur
    int l;// nb de case en largeur
    char** visuel;// aparence du vaiseau
};

struct Vaisseau{
    int x;//position x,y
    int y;
    int temp;// temps avant son apparition;
    Type cat;// la categorie de vaiseau (cat: 1, 2, ...)
    int vie;// le nb de vit reel du vaisseau
};


Type** type(int* max);

char* deroulement(void);






















#endif

