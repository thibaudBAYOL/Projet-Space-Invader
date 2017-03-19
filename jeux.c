#include <stdoi.h>
#include <stdlib.h>

#include <string.h>


#include <termios.h>
       #include <unistd.h> // terminos

#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h> // open


struct Type{
    int vit;// vitesse du tire en case / seconde
    int cad;// cadence de tire ex: 0.5
    char tir;// apparence du tire
    int vit;// vie par defaut
    
    int h;// nb de case en hauteur
    int l;// nb de case en largeur
    char** visuel;// aparence du vaiseau
}

struct Vaisseau{
    int x;//position x,y
    int y;
    
    struct Type cat;// la categorie de vaiseau (cat: 1, 2, ...)
    int vie;// le nb de vit reel du vaisseau
}
type def struct Vaisseau Vaisseau;

int main(int argc, const char* argv[]){



//lire les niveaux
    int nb_vaiseau=0;
    // lire les categories(type)
    // enregistrer les vaisseaux (dans un tableau)
    Vaiseau armer[nb_vaiseau]

// afficher les vaiseaux;






return EXIT_SUCCESS;
}


