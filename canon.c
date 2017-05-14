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


  void changePos(Vaisseau** troup){
    int ind,taille;
    int k = 0;
    while(troup[0][k].x != -5){
        ind = troup[0][k].cat.index;
        taille = troup[0][k].cat.lcycle;
        if((troup[0][k].cat.cycle[0][ind] == -1) && (troup[0][k].cat.cycle[1][ind] == -1)){            //Vérification du déplacement x
          troup[0][k].x -= 1;
          troup[0][k].y -= 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == -1) && (troup[0][k].cat.cycle[1][ind] == 0)){            //Vérification du déplacement x
          troup[0][k].x -= 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == -1) && (troup[0][k].cat.cycle[1][ind] == 1)){            //Vérification du déplacement x
          troup[0][k].x -= 1;
          troup[0][k].y += 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == 0) && (troup[0][k].cat.cycle[1][ind] == -1)){            //Vérification du déplacement x         
          troup[0][k].y -= 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == 0) && (troup[0][k].cat.cycle[1][ind] == 0)){            //Vérification du déplacement x
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == 0) && (troup[0][k].cat.cycle[1][ind] == 1)){            //Vérification du déplacement x
          troup[0][k].y += 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == 1) && (troup[0][k].cat.cycle[1][ind] == -1)){            //Vérification du déplacement x
          troup[0][k].x += 1;
          troup[0][k].y -= 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == 1) && (troup[0][k].cat.cycle[1][ind] == 0)){            //Vérification du déplacement x
          troup[0][k].x += 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }else if((troup[0][k].cat.cycle[0][ind] == 1) && (troup[0][k].cat.cycle[1][ind] == 1)){            //Vérification du déplacement x
          troup[0][k].x += 1;
          troup[0][k].y += 1;
            if(ind+1 < taille) troup[0][k].cat.index += 1; 
            else troup[0][k].cat.index = 0;
        }
        k++;
    }
    return;
  }

  void vaisseaux(char** carte, Vaisseau** troup, time_t* start, time_t* told, struct winsize w){
    //Calcule du tnew (actuel)
    //If tnew >= told + 1second
    //Modification des positions du troup
    int i,j;
    int k = 0;
    time_t tnew;
    time(&tnew);

    if((tnew - (*told)) >= 1){ //Si la différence est supérieure ou égale à 1 seconde, on bouge les vaisseaux
        changePos(troup);
        *told = tnew;
    }
    //int k = 0;
    //k = 0;
    time_t tnewCheck;
    time(&tnewCheck);
    while(troup[0][k].x != -5){
      if((troup[0][k].y >= 0) && (troup[0][k].y < w.ws_row-3) && (troup[0][k].x > 2) && (troup[0][k].x < w.ws_col-6) && (troup[0][k].temp < (tnewCheck-(*start)))){
        int y = (w.ws_row-3)-troup[0][k].y;
        int x = troup[0][k].x;
        for (i = 0; i < troup[0][k].cat.h; i++){
          for (j = 0; j < troup[0][k].cat.l; j++){
            //printf("%c", troup[0][0].cat.visuel[i][j]);
            carte[y+i][x+j] = troup[0][k].cat.visuel[i][j];
            //x++;
          }
          //x = troup[0][0].cat.x;
          //y++;
            //printf("\n");
        }
      }
      k++; 
    }
  }

  int gameover(char** carte, struct winsize w){
    int i,j;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
        }
        if(i == w.ws_row/2 && j == (w.ws_col/2)+4){
          carte[i][j-7] = 'G';carte[i][j-6] = 'A';carte[i][j-5] = 'M';carte[i][j-4] = 'E';
          carte[i][j-3] = 'O';carte[i][j-2] = 'V';carte[i][j-1] = 'E';carte[i][j] = 'R';
        }
      }
    }
    return -4;
  }

  int design(char** carte, Vaisseau** vais, time_t* start, time_t* told, int x, struct winsize w){ //x : 0 ou 1

    int i,j;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
        }
      }
    }
    /*
    int maxiV;
    Type** V1=type(&maxiV);
    Vaisseau** vais = creeUneArmer(&maxiV,V1);*/
    vaisseaux(carte, vais, start, told, w);

    //Test de collision ici !!!
    //Dessin du vaisseau joueur
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(i == (w.ws_row-3) && j == x){
              if(2 <= x && x < w.ws_col-3){ //EVITER LE DEBORDEMENT
                if(carte[i][j] == ' ') carte[i][j] = '*'; else{ if (gameover(carte, w) == -4) return -4; } 
              } 
            }
        if(i == (w.ws_row-2)){
          if(2 <= x && x < w.ws_col-3){ //EVITER LE DEBORDEMENT
            if(j == (x-1) || j == (x) || j == (x+1)){
              if(carte[i][j] == ' ') carte[i][j] = '*'; else{ if (gameover(carte, w) == -4) return -4; }
            }
          }
        }
        if(i == (w.ws_row-1)){
          if(carte[i][j] != '*') if(gameover(carte, w) == -4) return -4;
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
  char *affiche = malloc(sizeof(char)*w.ws_row*w.ws_col+w.ws_row);
  affiche[0] = '0';
  carte = malloc(sizeof(char*)*w.ws_row); //si remplacement faire CTRL+F et remplacer partout ou y'a 20
  int z = 0;
  for(z = 0;z < w.ws_row; z++ ){
    carte[z] = malloc(sizeof(char*)*w.ws_col);
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

    int maxiV;
    time_t told;
    time(&told);
    time_t start;
    time(&start);
    Type** V1=type(&maxiV);
    //int nbTV = maxiV; // Nombre de types de vaisseaux
    Vaisseau** vais = creeUneArmer(&maxiV,V1);
    design(carte, vais, &start, &told, xVar, w);


    struct pollfd fds[1];
    int n;
    fds[0].fd = 0;
    fds[0].events = POLLIN;
    char buf[1];

    int ret;
    while(1){
        poll(fds,1,100);
            if(fds[0].revents & POLLIN){
                if((n=read(fds[0].fd, buf, 1))>0){    //while((n=read(fds[0].fd, buf, 1))>0){
                  //write(STDOUT_FILENO, buf, n);
                  if(strcmp(buf, "q")==0){ 
                    xVar--;
                    if(xVar < 0+3) xVar++; //Evite le débordement
                    ret = design(carte, vais, &start, &told, xVar, w);
                    show(carte, affiche, w);
                    if(ret == -4){ canonique(&prev); exit(0);}
                  }else if(strcmp(buf, "d")==0){
                    xVar++;
                    if(xVar > w.ws_col-4) xVar--; //Evite le débordement
                    ret = design(carte, vais, &start, &told, xVar, w);
                    show(carte, affiche, w);
                    if(ret == -4){ canonique(&prev); exit(0);}
                  }else if(strcmp(buf, "p")==0){ 
                    canonique(&prev); exit(0);
                  }else if(strcmp(buf, " ")==0){ 
                    canonique(&prev); exit(0);
                  }
                }
            } else{ 
              ret = design(carte, vais, &start, &told, xVar, w);
              show(carte, affiche, w);
              if(ret == -4){ canonique(&prev); exit(0); }
              //printf("Nombre de types de vaisseaux : %d\n", nbTV);
            }
    }



    
    if (canonique(&prev)==-1)
      return 1;
    
    return 0;
  }