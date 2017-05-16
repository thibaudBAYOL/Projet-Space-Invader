
#ifndef thibaudSasi_0_f
#define thibaudSasi_0_f


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <sys/ioctl.h>
       #include <unistd.h> // terminos
#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h> // open


typedef struct Vaisseau Vaisseau;
typedef struct Type Type;
typedef struct Tire Tire;
typedef struct Power Power;

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
    int index; //index
};

struct Tire {
    int libre;
    int perso;
    int x;
    int y;
    int dega;// vie en moins
    double vit;
    char visu;
    struct timespec last;
};

struct Vaisseau{
    int x;//position x,y
    int y;
    int temp;
    int ecran;// temps avant son apparition;
    int player;
    Type cat;// la categorie de vaiseau (cat: 1, 2, ...)
    struct timespec cadOld;
};

struct Power{
    int x;//position x,y
    int y;
    int pow; //1,2,3,4;
    int valeur;
    double v_cad;
    struct timespec tStart;
    //char* visuel;
    int libre;// temps avant son apparition;
};


Type** type(int* max /*, char* adresse */);

char* deroulement(void /* char* adresse? */);

Vaisseau** creeUneArmer(int* max /*, char* adresse */, Type** T);

void tire(int x,int y,Vaisseau* A,int perso,Tire* t);

void majTire(char** carte,Vaisseau*** coord, Tire* t, struct winsize w);

void infos(char** carte, Vaisseau* joueur, struct winsize w, int n);

int melange(int a, int b);

void liberer(Tire* t);

void powerUpdate(char** carte, Vaisseau*** coord, Vaisseau* joueur, Power* powerUp, struct winsize w);

void powerLanch(Power* powerUp, struct winsize w);

#endif

