#include <stdio.h>
#include <stdlib.h>
  #include <termio.h>
  #include <unistd.h>
#include <sys/ioctl.h>
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


  void design(char** carte, int x, struct winsize w){ //x : 0 ou 1
    int i,j;
    for (i = 0; i < w.ws_row; ++i){
      for (j = 0; j < w.ws_col; ++j){
        if(j < 2  || j > (w.ws_col-3) || i < 1 || i > (w.ws_row-2)){
          carte[i][j] = '*';
        }else{
          carte[i][j] = ' ';
        }
        if(i == (w.ws_row-3) && j == x){
          if(2 <= x && x < w.ws_col-3){ //EVITER LE DEBORDEMENT
            carte[i][j] = '*';
          } 
        }
        if(i == (w.ws_row-2)){
          if(2 <= x && x < w.ws_col-3){ //EVITER LE DEBORDEMENT
            if(j == (x-1) || j == (x) || j == (x+1)){
              carte[i][j] = '*';
            }
          }
        }
      }
    }
    return;
  }



  /* exemple d'utilisation */
  int main (int argc,char *argv[])
  {
  struct termios prev;
  int nb,c;
  //pour récupérer la taille du terminal
  struct winsize w;
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    if (non_canonique(&prev)==-1)
      return 1;
    
  char **carte;
  carte = malloc(sizeof(char*)*w.ws_row); //si remplacement faire CTRL+F et remplacer partout ou y'a 20
  int z = 0;
  for(z = 0;z < w.ws_row; z++ ){
    carte[z] = malloc(sizeof(char*)*w.ws_col);
  }
  int xVar = w.ws_col/2;
  design(carte, xVar, w);
  int i;
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
    for(nb=0;;){
      /*
      printf ("lines %d\n", w.ws_row);
      printf ("columns %d\n", w.ws_col);
      */
      for (i = 0; i < w.ws_row; ++i){
        printf("%s", carte[i]);
      }
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
      }
      
      nb++;
      /*
      (void) printf("carac[%d]=(%d,%o,%x)",nb,c,c,c);
      if (c==127) {
        printf(" char=DEL\n%d caracteres\n",nb);
        break;
      }
      if (c>=32)
        printf(" char=%c\n",c);
      else
        printf("\n");
      */
    }
    
    if (canonique(&prev)==-1)
      return 1;
    
    return 0;
  }