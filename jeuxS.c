
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <termios.h>
       #include <unistd.h> // terminos, lseek

#include <sys/types.h> // lseek
       #include <sys/stat.h>
       #include <fcntl.h> // open

struct Type{
    int h;// nb de case en hauteur
    int l;// nb de case en largeur
    int vit;// vitesse du tire en case / seconde
    int cad;// cadence de tire ex: 0.5
    int vie;// vie par defaut
    char tir;// apparence du tire
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
	if (fd_deroulement==-1){
    exit(1);
  }
read(fd_deroulement,buf,15);						printf("%s",buf);
read(fd_deroulement,numNiveau,2);						printf("%d",atoi(numNiveau));

//buf[14]='/';
//buf[15]=numNiveau[0];
//buf[16]='\0';
//const char* cbuf=buf;
int fd_niveau=open("space_invaders/niveaux/0",O_RDONLY);
	if (fd_niveau==-1){
    exit(1);
  }

//lire les niveaux
char *char_lus = malloc(sizeof(char)*15);
int i = 0;
	while(read(fd_niveau,&char_lus[i],1) > 0 && char_lus[i] != '\n'){
    if(i < 15) i++;
  }

int nb_vaisseau = atoi(char_lus);
printf("\nnbV : %d\n",nb_vaisseau);

char niveau[1024];
int nb_read;
while((nb_read = read(fd_niveau,niveau,1024)) > 0){
      printf("%s\n", niveau);
    }

//INITIALISER UN DOUBLE TABLEAU
/*
char *char_lus2 = malloc(sizeof(char)*15);
i=0;

int j=0,k=0;

while(i < nb_read){
  while(niveau[i] != ' '){
      if(j == 0){
        //type de vaisseau niv[a][b]...
      }else if(j == 1){
        //second d'apparition
      }else if(j == 2){
        // X
      }else{
        if(niveau[i] == '\n') //a++; j=0;
        // Y
      } 
    i++;
  }
  j++;
}
*/


//struct Type cat[2]; PROBLEME D'INITIALISATION
//  struct Vaisseau* armee = (struct Vaisseau*)malloc(sizeof(struct Vaisseau)*nb_vaisseau); PROBLEME D'INITIALISATION
//  i = 0;


//int fd_vaisseaux=open("space_invaders/vaisseaux/0",O_RDONLY);



    // lire les categories(type)
    // enregistrer les vaisseaux (dans un tableau)
   // Vaisseau armer[nb_vaisseau]

// afficher les vaisseaux;






return EXIT_SUCCESS;
}


