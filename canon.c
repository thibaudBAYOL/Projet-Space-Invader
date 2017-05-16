#include <stdio.h>
#include <stdlib.h>
  #include <termio.h>
  #include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>

#include <poll.h>
#include <fcntl.h>

#include <time.h>

#include "fonction.h"
#define BILLION  1000000000L
//#include <conio.h> //_getch()





  /* cette fonction reconfigure le terminal, et stocke */
  /* la configuration initiale a l'adresse prev */
  int non_canonique (struct termios *prev){
  struct termios new;
    if (tcgetattr(fileno(stdin),prev)==-1) {
      perror("tcgetattr");
      return -1;
    }
    new.c_iflag=prev->c_iflag;
    new.c_oflag=prev->c_oflag;
    new.c_cflag=prev->c_cflag;
    new.c_lflag=0;
    new.c_cc[VMIN]=1;
    new.c_cc[VTIME]=0;
    if (tcsetattr(fileno(stdin),TCSANOW,&new)==-1) {
      perror("tcsetattr");
      return -1;
    }
    return 0;
  }

  /* cette fonction restaure le terminal avec la */
  /* configuration stockee a l'adresse prev */
  int canonique (struct termios *prev){
    return tcsetattr(fileno(stdin),TCSANOW,prev);
  }


  void changePos(Vaisseau** troup, int niv){
    int ind,taille;
    int k = 0;
    while(troup[niv][k].x != -5){
      //if(troup[niv][k].ecran == 1){
        ind = troup[niv][k].cat.index;
        taille = troup[niv][k].cat.lcycle;
        if((troup[niv][k].cat.cycle[0][ind] == -1) && (troup[niv][k].cat.cycle[1][ind] == -1)){            //Vérification du déplacement x
          troup[niv][k].x -= 1;
          troup[niv][k].y -= 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == -1) && (troup[niv][k].cat.cycle[1][ind] == 0)){            //Vérification du déplacement x
          troup[niv][k].x -= 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == -1) && (troup[niv][k].cat.cycle[1][ind] == 1)){            //Vérification du déplacement x
          troup[niv][k].x -= 1;
          troup[niv][k].y += 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == 0) && (troup[niv][k].cat.cycle[1][ind] == -1)){            //Vérification du déplacement x         
          troup[niv][k].y -= 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == 0) && (troup[niv][k].cat.cycle[1][ind] == 0)){            //Vérification du déplacement x
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == 0) && (troup[niv][k].cat.cycle[1][ind] == 1)){            //Vérification du déplacement x
          troup[niv][k].y += 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == 1) && (troup[niv][k].cat.cycle[1][ind] == -1)){            //Vérification du déplacement x
          troup[niv][k].x += 1;
          troup[niv][k].y -= 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == 1) && (troup[niv][k].cat.cycle[1][ind] == 0)){            //Vérification du déplacement x
          troup[niv][k].x += 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }else if((troup[niv][k].cat.cycle[0][ind] == 1) && (troup[niv][k].cat.cycle[1][ind] == 1)){            //Vérification du déplacement x
          troup[niv][k].x += 1;
          troup[niv][k].y += 1;
            if(ind+1 < taille) troup[niv][k].cat.index += 1; 
            else troup[niv][k].cat.index = 0;
        }
      //}
        k++;
      
    }
    return;
  }

  int vaisseaux(char** carte, Vaisseau*** coord, Vaisseau** troup, Tire* tires, struct timespec* start, struct timespec* told, int niv, struct winsize w){
    //Calcule du tnew (actuel)
    //If tnew >= told + 1second
    //Modification des positions du troup
    int i,j;
    int k = 0;

    double accum;
    struct timespec tnew;
    if(clock_gettime( CLOCK_REALTIME, &tnew) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    accum = (double)(tnew.tv_sec - (*told).tv_sec)+(double)(tnew.tv_nsec - (*told).tv_nsec)/BILLION;
/*
    time_t tnew;
    time(&tnew);
*/
    if(accum >= 0.25){ //Si la différence est supérieure ou égale à 1 seconde, on bouge les vaisseaux
        changePos(troup, niv);
        *told = tnew;
    }
    //int k = 0;
    //k = 0;
/*
    time_t tnewCheck;
    time(&tnewCheck);
*/
    int kill = 0;
    double accum2;
    struct timespec tnewCheck;
    if(clock_gettime( CLOCK_REALTIME, &tnewCheck) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    accum2 = (double)(tnewCheck.tv_sec - (*start).tv_sec)+(double)(tnewCheck.tv_nsec - (*start).tv_nsec)/BILLION; //A partir du début de partie.

    while(troup[niv][k].x != -5){
      if((troup[niv][k].cat.vie > 0) && (troup[niv][k].y >= 0) && (troup[niv][k].y < w.ws_row-3) && (troup[niv][k].x > 2) && (troup[niv][k].x < w.ws_col-6) && ((double)troup[niv][k].temp < accum2)){
        int y = (w.ws_row-3)-troup[niv][k].y;
        int x = troup[niv][k].x;
        for (i = 0; i < troup[niv][k].cat.h; i++){
          for (j = 0; j < troup[niv][k].cat.l; j++){
            //printf("%c", troup[niv][0].cat.visuel[i][j]);
            carte[y+i][x+j] = troup[niv][k].cat.visuel[i][j];
            coord[y+i][x+j] = &(troup[niv][k]);
            //x++;
          }
          
          //x = troup[niv][0].cat.x;
          //y++;
            //printf("\n");
        }
        if(troup[niv][k].ecran == 0) troup[niv][k].ecran = 1;
        tire((x+(x+j))/2, (y+i), &(troup[niv][k]), 0, tires);
      }else if(troup[niv][k].cat.vie <= 0){
        kill++;
      }
      k++; 
    }
    if(k == kill){
      return -3;
    }
      return 0;
  }

  int gamewon(char** carte, Vaisseau*** coord, struct winsize w){
    int i,j;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
          coord[i][j] = NULL; //sécurité
        }
        if(i == w.ws_row/2 && j == (w.ws_col/2)+4){
          carte[i][j-7] = 'G';carte[i][j-6] = 'A';carte[i][j-5] = 'M';carte[i][j-4] = 'E';
          carte[i][j-3] = ' ';carte[i][j-2] = 'W';carte[i][j-1] = 'O';carte[i][j] = 'N';
        }
      }
    }
    return -4;
  }

  int gameover(char** carte, Vaisseau*** coord, struct winsize w){
    int i,j;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
          coord[i][j] = NULL; //sécurité
        }
        if(i == w.ws_row/2 && j == (w.ws_col/2)+4){
          carte[i][j-7] = 'G';carte[i][j-6] = 'A';carte[i][j-5] = 'M';carte[i][j-4] = 'E';
          carte[i][j-3] = 'O';carte[i][j-2] = 'V';carte[i][j-1] = 'E';carte[i][j] = 'R';
        }
      }
    }
    return -4;
  }

  int gameend(char** carte, Vaisseau*** coord, struct winsize w){
    int i,j;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
          coord[i][j] = NULL; //sécurité
        }
        if(i == w.ws_row/2 && j == (w.ws_col/2)+4){
          carte[i][j-7] = 'G';carte[i][j-6] = 'A';carte[i][j-5] = 'M';carte[i][j-4] = 'E';
          carte[i][j-3] = ' ';carte[i][j-2] = 'E';carte[i][j-1] = 'N';carte[i][j] = 'D';
        }
      }
    }
    return -4;
  }

  int design(char** carte, Vaisseau*** coord, Vaisseau** vais, Vaisseau* joueur, Tire* tires, struct timespec* start, struct timespec* told, int x, int niv, struct winsize w){ //x : 0 ou 1

    int i,j,ret;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
          coord[i][j] = NULL;
        }
      }
    }
    /*
    int maxiV;
    Type** V1=type(&maxiV);
    Vaisseau** vais = creeUneArmer(&maxiV,V1);*/
    ret = vaisseaux(carte, coord, vais, tires, start, told, niv, w);
    if (ret == -3){ if (gamewon(carte, coord, w) == -4) return -3;}

    //Test de collision ici !!!
    //Dessin du vaisseau joueur
    if(joueur->cat.vie <= 0){
      if (gameover(carte, coord, w) == -4) return -4; 
    }
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(i == (w.ws_row-3) && j == x){
              if(2 <= x && x < w.ws_col-3){ //EVITER LE DEBORDEMENT
                if(carte[i][j] == ' '){ 
                  carte[i][j] = '*';
                  coord[i][j] = joueur; 
                }else{ if (gameover(carte, coord, w) == -4) return -4; } 
              } 
            }
        if(i == (w.ws_row-2)){
          if(2 <= x && x < w.ws_col-3){ //EVITER LE DEBORDEMENT
            if(j == (x-1) || j == (x) || j == (x+1)){
              if(carte[i][j] == ' '){ 
                carte[i][j] = '*';
                coord[i][j] = joueur;
              }else{ if (gameover(carte, coord, w) == -4) return -4; }
            }
          }
        }
        if(i == (w.ws_row-1)){
          if(carte[i][j] != '*') if(gameover(carte, coord, w) == -4) return -4;
        }
      }
    }
    return 0;
  }

  void show(char** carte, char* affiche, struct winsize w){
    int x = 0;
    int i;
    for(i = 0; i < w.ws_row; ++i){
      strncpy(affiche+x, carte[i] ,w.ws_col);
      if(i < w.ws_row-1) strcpy(affiche+x+w.ws_col, "\n");
      x += w.ws_col+1;
    }
    //x = 0;
    write(STDOUT_FILENO, affiche, w.ws_col*w.ws_row+w.ws_row);
    return;
  }



  /* exemple d'utilisation */
  int main (int argc,char *argv[]){

  struct termios prev;
  //int nb,c;
  //pour récupérer la taille du terminal
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (non_canonique(&prev)==-1)
      return 1;
    
  char **carte;
  Vaisseau ***coord;
  char *affiche = malloc(sizeof(char)*w.ws_row*w.ws_col+w.ws_row);
  affiche[0] = '0';
  carte = malloc(sizeof(char*)*w.ws_row); //si remplacement faire CTRL+F et remplacer partout ou y'a 20
  coord = malloc(sizeof(char*)*w.ws_row);
  int z = 0;
  for(z = 0;z < w.ws_row; z++ ){
    carte[z] = malloc(sizeof(char*)*w.ws_col);
    coord[z] = malloc(sizeof(char*)*w.ws_col);
  }
  int xVar = w.ws_col/2;
  //int i;
/*
  int i,j;
  for (i = 0; i < w.ws_row; ++i){
    for (j = 0; j < w.ws_col; ++j){
      if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
        carte[i][j] = '*';
      }else{
        carte[i][j] = ' ';
      }
      if(i == (w.ws_row-3) && j == w.ws_col/2){
        carte[i][j] = '*';
      }
      if(i == (w.ws_row-2)){
        if(j == (w.ws_col/2-1) || j == (w.ws_col/2) || j == (w.ws_col/2+1)){
          carte[i][j] = '*';
        }
      }
    }
  }
*/
    //char test[10];
      /*
      printf ("lines %d\n", w.ws_row);
      printf ("columns %d\n", w.ws_col);
      */
/*
    for(nb=0;;){

      show(carte, affiche, w);
      
      //for(i = 0; i < w.ws_row; ++i){
        //printf("%s", carte[i]);
      //}
                                                          //read(0, test, 3);
                                                          //if(test=="a") printf("gauche\n");
                                                          //if(test=="p") printf("droite\n");
                                                          //printf("%s\n", test);
                                                          //int ch1 = getch();

      c=getchar();
      if(c==113){ //gauche
        xVar--;
        design(carte, xVar, w);
      }else if(c==100){//droite
        xVar++;
        design(carte, xVar, w);
      } else if(c=='p'){
        canonique(&prev);
        return 1;
      }
      
      nb++;
                                                          
                                                          //(void) printf("carac[%d]=(%d,%o,%x)",nb,c,c,c);
                                                          //if (c==127) {
                                                            //printf(" char=DEL\n%d caracteres\n",nb);
                                                            //break;
                                                          //}
                                                          //if (c>=32)
                                                            //printf(" char=%c\n",c);
                                                          //else
                                                            //printf("\n");
                                                          
    }
*/


    Vaisseau joueur;
    joueur.cat.vit = 20;
    joueur.cat.cad = 4.; //double
    joueur.cat.tir = '^';
    joueur.cat.deg = 20;
    joueur.cat.vie = 3;
    struct timespec cadOld1;
    if(clock_gettime( CLOCK_REALTIME, &cadOld1) == -1 ){
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    joueur.cadOld = cadOld1;

    Tire tires[100];
    int i2;
    for (i2 = 0; i2 < 100; ++i2){
      tires[i2].libre = 1;
    }

    int maxiV;
    
    struct timespec start, told;
    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    if( clock_gettime( CLOCK_REALTIME, &told) == -1 ){
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
/*
    time_t told;
    time(&told);
    time_t start;
    time(&start);// char** mod=finddir(); while(1){    
*/
    int niv = 0;
    Type** V1=type(&maxiV,"space_invaders");//mod[m]
    //int nbTV = maxiV; // Nombre de types de vaisseaux
    Vaisseau** vais = creeUneArmer(&maxiV,"space_invaders",V1);//mod[m]
    design(carte, coord, vais, &joueur, tires, &start, &told, xVar, niv, w);


    struct pollfd fds[1];
    int n;
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    char buf[3];

    int ret;
    while(1){
        poll(fds,1,10);
        
            if(fds[0].revents & POLLIN){
                if((n=read(fds[0].fd, buf, 3))>0){    //while((n=read(fds[0].fd, buf, 1))>0){
                  //write(STDOUT_FILENO, buf, n);
                  if(buf[0]==27 && buf[1]==91 && buf[2]==68){//strcmp(buf, "q")==0){ 
                    xVar--;
                    if(xVar < 0+3) xVar++; //Evite le débordement
                    /*ret = design(carte, coord, vais, &start, &told, xVar, w);
                    majTire(carte, coord, tires);
                    show(carte, affiche, w);
                    if(ret == -4){ canonique(&prev); exit(0);}*/
                  }else if(buf[0]==27 && buf[1]==91 && buf[2]==67){//strcmp(buf, "d")==0){
                    xVar++;
                    if(xVar > w.ws_col-4) xVar--; //Evite le débordement
                    /*ret = design(carte, coord, vais, &start, &told, xVar, w);
                    majTire(carte, coord, tires);
                    show(carte, affiche, w);
                    if(ret == -4){ canonique(&prev); exit(0);}*/
                  }else if(buf[0]==27 && buf[1]==91 && buf[2]==66){//strcmp(buf, "p")==0){
                    canonique(&prev); exit(0);
                  }else if(buf[0]==27 && buf[1]==91 && buf[2]==65){//strcmp(buf, " ")==0){ 
                    tire(xVar,(w.ws_row-4),&joueur,1,tires);//canonique(&prev); exit(0);
                  }
                }
            }
            ret = design(carte, coord, vais, &joueur, tires, &start, &told, xVar, niv, w);
            majTire(carte, coord, tires, w);
            show(carte, affiche, w);
            if(ret == -4){ canonique(&prev); exit(0); 
            }else if(ret == -3){
              while((n=read(fds[0].fd, buf, 1))>0){
                if(buf[0]==27 && buf[1]==91 && buf[2]==66){//strcmp(buf, "p")==0){
                  canonique(&prev); exit(0);
                }else if(buf[0]==27 && buf[1]==91 && buf[2]!=66){//strcmp(buf, "\n")==0){
                  if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
                    perror( "clock gettime" );
                    exit( EXIT_FAILURE );
                  } 
                  niv++; 
                  break; // Ajouter condition pour connaitre la fin des niveaux. 
                }  
              }
            }
            //printf("Nombre de types de vaisseaux : %d\n", nbTV);
            if(vais[niv] == NULL) { 
              if(gameend(carte, coord, w) == -4){
                  show(carte, affiche, w);
              } 
              break; 
            }
    }

//m++;}

    
    if (canonique(&prev)==-1)
      return 1;
    
    return 0;
  }
