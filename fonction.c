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

int lire(char** t);
double lire2(char** t);


char* deroulement(){

int fd_deroulement=open("space_invaders/deroulement",O_RDONLY);
	if (fd_deroulement==-1)exit(1);
	int max=lseek(fd_deroulement,0,SEEK_END); max=max-15;
char totoNiveau[max];
lseek(fd_deroulement,15,SEEK_SET);
read(fd_deroulement,totoNiveau,max);

close(fd_deroulement);

int i,j;int cpt=0;
for (i=0;i<max;i++){
	if (totoNiveau[i]=='\n') cpt++;
}
char* numNiveau= malloc( (cpt+2)*sizeof(char));
j=0;
for (i=0;i<=cpt+1 && j<=max;i++){
	if (j>max)break;
	numNiveau[i]=totoNiveau[j];// (si <10)
	j=j+2;
}
return numNiveau;
}


int lire(char** tt){
int i=0;char tab[]="          ";
	char* t=*tt;		
while(  t[i]!=' ' && t[i]!='\n' && i<10){
	tab[i]=t[i];i++;			
}					
(*tt)=t+i+1;// adresse
int rep;
 rep=atoi(tab);//(int)strtol(tab,NULL,10);
return rep;
}

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




Type** type(int* max){
int fd_v=-1;
char i='0';	
char vaiseaux[]="space_invaders/vaisseaux/-";	

*max=0;
do{
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
Type* type2=malloc(sizeof(Type));
*type2=type1;

return type2;
}







int main(int argc, const char* argv[]){

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


return EXIT_SUCCESS;
}


