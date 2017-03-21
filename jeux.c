
#include <stdio.h>
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
    int vie;// vie par defaut
    
    int h;// nb de case en hauteur
    int l;// nb de case en largeur
    char** visuel;// aparence du vaiseau
};

struct Vaisseau{
    int x;//position x,y
    int y;
    
    struct Type cat;// la categorie de vaiseau (cat: 1, 2, ...)
    int vie;// le nb de vit reel du vaisseau
};
typedef struct Vaisseau Vaisseau;

int main(int argc, const char* argv[]){

char numNiveau[2];
char buf[40];
int fd_deroulement=open("space_invaders/deroulement",O_RDONLY);
	if (fd_deroulement==-1)exit(1);
	read(fd_deroulement,buf,15);						printf("%s",buf);
	read(fd_deroulement,numNiveau,2);						printf("%s",numNiveau);

//buf[14]='/';
//buf[15]=numNiveau[0];
//buf[16]='\0';
//const char* cbuf=buf;
 int fd_niveau=open("space_invaders/niveaux/0",O_RDONLY);
	if (fd_niveau==-1)exit(1);

//lire les niveaux
    char nb_vaisseau;
	read(fd_niveau,&nb_vaisseau,1);			printf("nbV:%c\n",nb_vaisseau);





    // lire les categories(type)
    // enregistrer les vaisseaux (dans un tableau)
   // Vaisseau armer[nb_vaisseau]

// afficher les vaisseaux;






return EXIT_SUCCESS;
}


