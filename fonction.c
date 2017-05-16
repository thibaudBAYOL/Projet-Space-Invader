/*
#include <stdio.h>
#include <stdlib.h>

#include <string.h>


#include <termios.h>
       #include <unistd.h> // terminos

#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h> // open
*/

#include "fonction.h"

#include <time.h>
#define BILLION  1000000000L
int lire(char** t);
double lire2(char** t);
Type* type01(int fd_v);




/*
* 
*/
char* deroulement(/* char* adresse? */){
			 /* adresse */
	int fd_deroulement=open("space_invaders/deroulement",O_RDONLY);
	if (fd_deroulement==-1)exit(1);
	int max = lseek(fd_deroulement,0,SEEK_END); max=max-15;
	char totoNiveau[max];
	lseek(fd_deroulement,15,SEEK_SET); /**/
	read(fd_deroulement,totoNiveau,max);

	close(fd_deroulement);

	int i,j;int cpt=0;
	for (i=0;i<max;i++){
		if (totoNiveau[i]=='\n') cpt++;  /*cpt = Compteur de ligne du fichier déroulement*/
	}
	char* numNiveau= malloc( (cpt)*sizeof(char)); /*MODIF : (cpt+2)*sizeof(char)*/
	j=0;
	for (i=0;i<=cpt+1 && j<=max;i++){
		if (j>max)break;
		numNiveau[i]=totoNiveau[j];// (si <10)   /*numNiveau = contient les numéros des niveaux présent dans le fichier déroulement*/
		j=j+2;
	}
return numNiveau; /*Retourne le tableau de niveaux*/
}

/*
* renvoi la lecture à partir du pointer de char **tt en int 
*/
int lire(char** tt){
	int i=0;char tab[]="          ";
		char* t=*tt;		
	while(  t[i]!=' ' && t[i]!='\n' && i<10){
		tab[i]=t[i];i++;			
	}					
	(*tt)=t+i+1;// adresse    /*déplace le pointer du flux après l'espace ou le "\n" de 1*/
	int rep;
	rep=atoi(tab);//(int)strtol(tab,NULL,10);
return rep;
}

/**
* renvoi la lecture à partir du pointer de char **tt en double
*/
double lire2(char** tt){
		int i=0;char tab[10];
		char* t=*tt;
	while(  t[i]!=' ' && t[i]!='\n' && i<10){
		tab[i]=t[i];i++;
	}
	(*tt)=t+i+1;// adresse
	double rep;
	rep=atof(tab);//double
return rep;
}

/**
* max : nombre de types de vaisseaux 
* Renvoi un double tableaux avec tous les types existantes de vaisseaux
*/

Type** type(int* max /*, char* adresse */ ){
	int fd_v=-1;
	char i='0';	 /* adresse */
	char vaiseaux[]="space_invaders/vaisseaux/-";

	*max=0;
	do{ /*vérifie l'ouverture des fichiers de type de vaisseaux et renvoi le nombre dans max*/
	 	vaiseaux[25]=i;
	//int i en char a ? //ou //char vaiseaux[10]=sprintf("vaiseaux%c",i);
	 	fd_v=open(vaiseaux,O_RDONLY);
	 	if (fd_v!=-1){
			close(fd_v);
			(*max)++;
			i++;
		 }
	}while(fd_v!=-1);

	Type** types=malloc((*max)*sizeof(Type*));
	int j=0;i='0';
	do{
	 	vaiseaux[25]=i;
	//int i en char a ? //ou //char vaiseaux[10]=sprintf("vaiseaux%c",i);
	 	fd_v=open(vaiseaux,O_RDONLY);
	 	if (fd_v!=-1){
			types[j]=type01(fd_v);
	 	}
	 	i++;j++;
	}while(j<(*max) && fd_v!=-1);
	return types;
}

/**
* renvoi la structure d'un type de vaisseau (close le descripteur de fichier crée dans le type) avec les informations lu dans le fichier
*/

Type* type01(int fd_v){

	int max= lseek(fd_v,0,SEEK_END);
		lseek(fd_v,0,SEEK_SET);
	char tab0[max];
	read(fd_v,tab0,max);
	close(fd_v);
	  char* tab=tab0;


	Type type1;

	type1.l=lire(&tab);
	type1.h=lire(&tab);

	type1.lcycle =lire(&tab);

	int i;
	int* x=malloc (type1.lcycle*sizeof(int));
	for (i=0;i<(type1.lcycle);i++){
		x[i]=lire(&tab);
	}

	int* y=malloc (type1.lcycle*sizeof(int));
	for (i=0;i<(type1.lcycle);i++){
		y[i]=lire(&tab);
	}

	int** cyl=malloc (2*sizeof(char*));
	cyl[0]=x; cyl[1]=y;
	type1.cycle=cyl;

	type1.vie=lire(&tab);
	type1.cad=lire2(&tab);// modif int en double????
	type1.vit=lire(&tab); 
	type1.deg=lire(&tab);
	type1.tir=tab[0];tab=tab+2;

	int j;char* h;
	
	char** vu=malloc(type1.h*sizeof(char*));
	for(i=0;i<type1.h;i++){
		h=malloc(type1.l*sizeof(char));
		for(j=0;j<type1.l;j++){
			h[j]=tab[j];
		}
		tab=tab+type1.l+1;
		vu[i]=h;
	}
	type1.visuel=vu;
	type1.index = 0;
	Type* type2=malloc(sizeof(Type));
	*type2=type1;

	return type2;
}

/*
* renvoi un double tableau de tous les vaisseaux par niveaux
* Type **T = tous les types de vaisseaux
*/

Vaisseau** creeUneArmer(int* max /*, char* adresse */, Type** T){	
	int fd_v=-1;
	char i='0';	 /* adresse */
	char vaiseaux[]="space_invaders/niveaux/-";	

	struct timespec cadOld1;
	    if(clock_gettime( CLOCK_REALTIME, &cadOld1) == -1 ){
	      perror( "clock gettime" );
	      exit( EXIT_FAILURE );
	    }

	*max=0;
	do{
	 	vaiseaux[23]=i;
	//int i en char a ? //ou //char vaiseaux[10]=sprintf("vaiseaux%c",i);
	 	fd_v=open(vaiseaux,O_RDONLY);
	 	if (fd_v!=-1){
			close(fd_v);
			(*max)++;
			i++;
		 }
	}while(fd_v!=-1);

	Vaisseau** V=malloc((*max+1)*sizeof(Vaisseau*));
	int j=0;i='0'; int maxi =0; int cap=0;int z=0;
	/*maxi = taille du fichier ; cap = nombre de vaisseau*/
	do{
	 	vaiseaux[23]=i;
	 	//printf("%s\n", vaiseaux);
	//int i en char a ? //ou //char vaiseaux[10]=sprintf("vaiseaux%c",i);
	 	fd_v=open(vaiseaux,O_RDONLY);
			
	 	maxi= lseek(fd_v,0,SEEK_END);
			lseek(fd_v,0,SEEK_SET);
		char tab0[maxi];
		read(fd_v,tab0,maxi);
		//close(fd_v);
		char* tab=tab0;
	 	if (fd_v!=-1){ 
	 		cap=lire(&tab);

			V[j]=malloc((cap+1)*sizeof(Vaisseau));

			for (z=0;z<cap;z++){
				V[j][z].cat=(*T[lire(&tab)]);
				//printf("t1 : %d\n", V[j][z].temp);
				V[j][z].temp=lire(&tab);
				//printf("t2 : %d\n", V[j][z].temp);
				//printf("x1 : %d\n", V[j][z].x);
				V[j][z].x=lire(&tab);
				//printf("x2 : %d\n", V[j][z].x);
				//printf("y1 : %d\n", V[j][z].y);
				V[j][z].y=lire(&tab);
				//printf("y2 : %d\n", V[j][z].y);
				V[j][z].ecran = 0;
				V[j][z].player = 0;
				V[j][z].cadOld = cadOld1;
			}
			V[j][z].x = -5;
			V[j][z].y = -5;
		} //else printf("sdfdfdfgd\n");
	 	i++;j++;
	 	close(fd_v);
	}while(j<(*max) && fd_v!=-1);
V[j]=NULL;
return V;
}

void liberer(Tire* t){
	int i = 0;
	for(i = 0; i < 100; ++i){
		t[i].libre = 1;
	}
	return;
}

void tire(int x,int y,Vaisseau* A,int perso,Tire* t){// Ajoute un tire en fonction de la
	
	double accum;
    struct timespec newTime;
    if(clock_gettime( CLOCK_REALTIME, &newTime) == -1 ){
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
    accum = (double)(newTime.tv_sec - A->cadOld.tv_sec)+(double)(newTime.tv_nsec - A->cadOld.tv_nsec)/BILLION;

	if ( accum >= 1./(A->cat.cad)){

		int i=0;
			while(i<100 && t[i].libre!=1){
				i++;
			}

			if (i<100){
				Tire T;
				T.perso=perso;
				T.libre=0;
				T.x=x;
				T.y=y;
				T.dega=A->cat.deg;
				T.visu=A->cat.tir;
				T.vit=(1./(double)A->cat.vit);
				T.last = newTime;
				t[i]=T;
			}
	A->cadOld = newTime;
	}
	return;
}

void majTire(char** carte, Vaisseau*** coord, Tire* t, struct winsize w){// affiche le tire // retire la vie s'il touche un vaiseau// fin du parcour du tire// depalcement du tire.

double accum;
    struct timespec newTime;
    if(clock_gettime( CLOCK_REALTIME, &newTime) == -1 ){
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

int i;int x; int y;
	for(i=0;i<100;i++){	
		if (t[i].libre==0){
		accum = (double)(newTime.tv_sec - t[i].last.tv_sec)+(double)(newTime.tv_nsec - t[i].last.tv_nsec)/BILLION;
		x=t[i].x;
		y=t[i].y;
			if( accum >= (t[i].vit) ){
					if (t[i].perso==1){
						t[i].y=y-1;
					}else{
						t[i].y=y+1;
					}
					t[i].last = newTime;
					
			}
			if (t[i].y<=1 || t[i].y >= w.ws_row-1){ t[i].libre=1;}
			//x=t[i].x; 
			if(t[i].y > 0 && t[i].y < w.ws_row-1){ 
				y = t[i].y;
				if(coord[y][x]!=NULL){
				 	coord[y][x]->cat.vie=coord[y][x]->cat.vie-t[i].dega;
					t[i].libre=1;
				 }else if (y > 0 && y < w.ws_row-1){
					carte[y][x]=t[i].visu;
				}
			}
		}
	}
	return;
}

int melange(int a, int b) {
 return rand()%(b-a)+a;
}

void powerUpdate(char** carte, Vaisseau*** coord, Vaisseau* joueur, Power* powerUp, struct winsize w){
	//powerLanch(powerUp, w);
	if((*powerUp).libre == 0){	
		int x,y;
		x = powerUp->x;
		y = powerUp->y;
		int power = (*powerUp).pow;
		carte[y][x-1] = '('; 
			if(power == 1){
				carte[y][x] = 'V';
			}else if(power == 2){
				carte[y][x] = 'D';
			}else if(power == 3){
				carte[y][x] = 'C';
			}else if(power == 4){
				carte[y][x] = 'S';
			}
		carte[y][x+1] = ')';
		
		int vrai = 0;
		if((coord[y][x-1] != NULL) || (coord[y][x] != NULL) || (coord[y][x+1] != NULL)){
			if(coord[y][x-1] != NULL){ if (coord[y][x-1]->player == 1){x = x-1; vrai = 1;}}
			if(coord[y][x] != NULL){ if (coord[y][x]->player == 1){ vrai = 1;}}
			if(coord[y][x+1] != NULL){ if (coord[y][x+1]->player == 1){x = x+1; vrai = 1;}} 
			if(vrai == 1){
				if(power == 1){
					coord[y][x]->cat.vie = coord[y][x]->cat.vie + (*powerUp).valeur; 
				}else if(power == 2){
					coord[y][x]->cat.deg = coord[y][x]->cat.deg + (*powerUp).valeur;
				}else if(power == 3){
					coord[y][x]->cat.cad = coord[y][x]->cat.cad + (*powerUp).v_cad;
				}else if(power == 4){
					coord[y][x]->cat.vit = coord[y][x]->cat.vit + (*powerUp).valeur;
				}
				(*powerUp).libre = 1;
				vrai = 0;
			}
		}
		if(y < w.ws_row-2) powerUp->y += 1;
		double accum;
		struct timespec pNow;
	    if(clock_gettime( CLOCK_REALTIME, &pNow) == -1 ){
	      perror( "clock gettime" );
	      exit( EXIT_FAILURE );
	    }
	    accum = (double)(pNow.tv_sec - powerUp->tStart.tv_sec)+(double)(pNow.tv_nsec - powerUp->tStart.tv_nsec)/BILLION;
	    if(accum >= 3.0){
	    	(*powerUp).libre = 1;
	    }
	}
	return;
}

void powerLanch(Power* powerUp, struct winsize w){
	int rnd = melange(0, 100);
	if ((powerUp->libre == 1) && (rnd < 10)){
		Power powUp;
		powUp.x = melange(3, (w.ws_col-6));
		powUp.y = w.ws_row-4;
		powUp.pow = melange(1,5); //entre 1 et 4 (5 exclusif)
		if((powUp.pow == 2)||(powUp.pow == 4)){
			powUp.valeur = melange(1,4);
		}else if(powUp.pow == 1){
			powUp.valeur = 1;
		}else{
			powUp.valeur = 0;
			powUp.v_cad = 0.5;
		}
		struct timespec pTime;
	    if(clock_gettime( CLOCK_REALTIME, &pTime) == -1 ){
	      perror( "clock gettime" );
	      exit( EXIT_FAILURE );
	    }
	    powUp.tStart = pTime;
		/*char* vu = malloc(sizeof(char)*4);
		vu[0] = '(';vu[2] = ')';
		if((powUp.pow == 1)){
			vu[1] = 'V';
		}else if((powUp.pow == 2)){
			vu[1] = 'D';
		}else if((powUp.pow == 3)){
			vu[1] = 'C';
		}else {
			vu[1] = 'S';
		}
		powUp.visuel = vu;*/
		powUp.libre = 0;
		(*powerUp) = powUp;
	}
	return;
}

void infos(char** carte, Vaisseau* player, struct winsize w, int n){
	int i,j,vit,deg,vie;
	double cad;
	char c = '1';
	i = 0;
	while(i < n){
		c++;
		i++;
	}
	vit = player->cat.vit;
	char cvit[3];
	sprintf(cvit, "%d", vit);
	deg = player->cat.deg;
	char cdeg[3];
	sprintf(cdeg, "%d", deg);
	cad = player->cat.cad;
	char ccad[7];
	sprintf(ccad, "%.1f", cad);
	vie = player->cat.vie;
	char cvie[3];
	sprintf(cvie, "%d", vie);
	
    for (i = 0; i < w.ws_row/2; ++i){
      for (j = 0; j < w.ws_col; ++j){

      	if(i == 1 && j == 14 ){
          carte[i][j-9] = 'v';carte[i][j-8] = 'i';carte[i][j-7] = 't';carte[i][j-6] = 'e';
          carte[i][j-5] = 's';carte[i][j-4] = 's';carte[i][j-3] = 'e';carte[i][j-2] = ':';
          carte[i][j-1] = cvit[0];if(vit > 9) carte[i][j] = cvit[1];
        }

        if(i == 2 && j == 12 ){
          carte[i][j-7] = 'd';carte[i][j-6] = 'e';carte[i][j-5] = 'g';carte[i][j-4] = 'a';
          carte[i][j-3] = 't';carte[i][j-2] = ':';carte[i][j-1] = cdeg[0];if(deg > 9) carte[i][j] = cdeg[1];
        }

        if(i == 1 && j == (w.ws_col/2)+4){
          carte[i][j-7] = 'L';carte[i][j-6] = 'e';carte[i][j-5] = 'v';carte[i][j-4] = 'e';
          carte[i][j-3] = 'l';carte[i][j-2] = ' ';carte[i][j-1] = c;//carte[i][j] = 'N';
        }

        if(i == 1 && j == w.ws_col-6 ){
       	  if(cad < 10.){ carte[i][j-11] = ccad[0];carte[i][j-10] = '.';carte[i][j-9] = ccad[2];}
       	  else if(cad >= 10.){ carte[i][j-12] = ccad[0];carte[i][j-11] = ccad[1];carte[i][j-10] = '.';carte[i][j-9] = ccad[3];}
       	  carte[i][j-8] = ':';
          carte[i][j-7] = 'c';carte[i][j-6] = 'a';carte[i][j-5] = 'd';carte[i][j-4] = 'e';
          carte[i][j-3] = 'n';carte[i][j-2] = 's';carte[i][j-1] = 'e';carte[i][j] = ' ';
          //carte[i][j] = ' ';
        }

        if(i == 2 && j == w.ws_col-4 ){
          carte[i][j-8] = cvie[0];if(vie > 9) carte[i][j-7] = cvie[1];carte[i][j-6] = ':';
          carte[i][j-5] = 'v';carte[i][j-4] = 'i';carte[i][j-3] = 'e';carte[i][j-2] = ' ';
          carte[i][j-1] = ' ';//carte[i][j-2] = ' ';carte[i][j-1] = c;//carte[i][j] = 'N';
        }
      }
    }
	return;
}
//////////////////////////TESTE/////////////////////////////////////

//int main(int argc, const char* argv[]){
/*	double a1 = 8.5;
    double a2 = 15.3;
    char ca1[5];
    char ca2[5];
    sprintf(ca1, "%.1f", a1);
    sprintf(ca2, "%.1f", a2);
    printf("%s\n", ca1);
    printf("%s\n", ca2);
*/
	/*srand(time(NULL));
	for (int i = 0; i < 10; ++i){
		printf("%d\n", melange(1,4));
	}*/
	
	/*
	struct timespec start, stop;
    double accum;

    if( clock_gettime( CLOCK_REALTIME, &start) == -1 ){
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }

//    system( argv[1] );
sleep(2);
    for (int i = 0; i < 100000; ++i){
    	i += 1;
    	i -= 1;
    }
    if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) {
      perror( "clock gettime" );
      exit( EXIT_FAILURE );
    }
//    printf("%lf\n", (double)stop.tv_nsec/BILLION);
    accum = (double)(stop.tv_sec - start.tv_sec)+(double)(stop.tv_nsec - start.tv_nsec)/BILLION;
    printf( "%lf\n", accum );
    */

    /*
time_t t;
time(&t);
printf("%ld\n", t);
sleep(2);
time(&t);
printf("%ld\n", t);
*/


/*
//  deroulement
			printf("deroulement:\n");
char* tab=deroulement();
int i=0;
		while (tab[i]!='\0'){printf("%c:%d ",tab[i],i);i++;}printf("\n");

free(tab);//free

// fin deroulement

// vaiseaux0 Type
			printf("Type\n");
int maxiV;
Type** V1=type(&maxiV);
			printf("maxiV=%d\n",maxiV);

//aff(V[z]);

Type* V=V1[0];
			printf("test:\n");
printf("h:%d\n",V->h);// nb de case en hauteur
printf("l:%d\n",V->l);// nb de case en largeur

printf("%d\n",V->lcycle);

for (i=0;i<V->lcycle; i++){
printf("%d ",V->cycle[0][i]);
    }
printf("\n");
for (i=0;i<V->lcycle; i++){
printf("%d ",V->cycle[1][i]);
    }
printf("\n");

printf("%d\n",V->vie);// vie par defaut
printf("%d\n",V->vit);// vitesse du tire en case / seconde
printf("%f\n",V->cad);// cadence de tire ex: 0.5
printf("%c\n",V->tir);// apparence du tire
printf("%d\n",V->deg);// 			les degats engendre

int j;
for(i=0;i<V->h;i++){
for(j=0;j<V->l;j++){
printf("%c",V->visuel[i][j]);// aparence du vaiseau
}
printf("\n");
}
printf("\n");


free(V->cycle[0]);// free
free(V->cycle[1]);
free(V->cycle);


for(i=0;i<V->h;i++){
	free(V->visuel[i]);
}
free(V->visuel);

free(V1);

// fin type

Vaisseau** vais = creeUneArmer(&maxiV,V1);
printf("temp : %d\n", vais[0][0].temp);
printf("x : %d\n", vais[0][0].x);
printf("y : %d\n", vais[0][0].y);
printf("vie : %d\n", vais[0][0].vie);

for (i = 0; i < vais[0][0].cat.h; i++){
	for (j = 0; j < vais[0][0].cat.l; j++){
		printf("%c", vais[0][0].cat.visuel[i][j]);
	}
	printf("\n");
}*/
	/*
printf("%c", vais[0][0].cat.visuel[0][0]);
printf("%c", vais[0][0].cat.visuel[0][1]);
printf("%c", vais[0][0].cat.visuel[0][2]);
printf("%c", vais[0][0].cat.visuel[0][3]);
printf("%c", vais[0][0].cat.visuel[0][4]);
printf("\n");
printf("%c", vais[0][0].cat.visuel[1][0]);
printf("%c", vais[0][0].cat.visuel[1][1]);
printf("%c", vais[0][0].cat.visuel[1][2]);
printf("%c", vais[0][0].cat.visuel[1][3]);
printf("%c", vais[0][0].cat.visuel[1][4]);
printf("\n");
printf("%c", vais[0][0].cat.visuel[2][0]);
printf("%c", vais[0][0].cat.visuel[2][1]);
printf("%c", vais[0][0].cat.visuel[2][2]);
printf("%c", vais[0][0].cat.visuel[2][3]);
printf("\n");
printf("%c", vais[0][0].cat.visuel[2][4]);
//printf("\n");
*/
//return EXIT_SUCCESS;
//}


