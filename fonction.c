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

	Vaisseau** V=malloc((*max)*sizeof(Vaisseau*));
	int j=0;i='0'; int maxi =0; int cap=0;int z=0;
	/*maxi = taille du fichier ; cap = nombre de vaisseau*/
	do{
	 	vaiseaux[23]=i;
	 	printf("%s\n", vaiseaux);
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

			V[j]=malloc( (cap)*sizeof(Vaisseau) );

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
			V[j][z].vie=V[j][z].cat.vie;
			}
		} //else printf("sdfdfdfgd\n");
	 	i++;j++;
	 	close(fd_v);
	}while(j<(*max) && fd_v!=-1);

return V;
}




//////////////////////////TESTE/////////////////////////////////////
/*
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
*//*
return EXIT_SUCCESS;
}*/


