
#include <stdio.h>
#include <stdlib.h>

#include <string.h>


#include <termios.h>
       #include <unistd.h> // terminos

#include <sys/types.h>
       #include <sys/stat.h>
       #include <fcntl.h> // open

typedef struct Vaisseau Vaisseau;
typedef struct Type Type;

Type* type01(int fd_v);
char* deroulement();
int lire(char* t,int a,int* l);
Type** type(int* max);

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
};

struct Vaisseau{
    int x;//position x,y
    int y;
    int temp;// temps avant son apparition;
    Type cat;// la categorie de vaiseau (cat: 1, 2, ...)
    int vie;// le nb de vit reel du vaisseau
};







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


int lire(char* t,int a,int* l){
int i=0;char tab[10];

while(  t[i]!=' ' && t[i]!='\n' && i<10){
	tab[i]=t[i];i++;
}
(*l)=i+2;// adresse
int rep; printf("%s$\n",tab);
if (a==0) rep=atoi(tab);//(int)strtol(tab,NULL,10);
if (a==1) rep=atof(tab);//double
return rep;
}




Type** type(int* max){
int fd_v=-1;
char i='0';	
char vaiseaux[]="space_invaders/vaisseaux/-";	

*max=0;
do{
 	vaiseaux[25]=i;
		printf("1@%s@\n",vaiseaux);
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
	printf("2@%s@\n",vaiseaux);
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
int l=0;
Type type1;
type1.l=lire(tab,0,&l);tab=tab+l;
type1.h=lire(tab,0,&l);tab=tab+l;

type1.lcycle =lire(tab,0,&l);tab=tab+l;

int i;
int* x=malloc (type1.lcycle*sizeof(int));
for (i=0;i<=(type1.lcycle);i++){
	x[i]=lire(tab,0,&l);tab=tab+l;
}

int* y=malloc (type1.lcycle*sizeof(int));
for (i=0;i<=type1.lcycle;i++){
	y[i]=lire(tab,0,&l);tab=tab+l;
}

int** cyl=malloc (2*sizeof(char*));
cyl[0]=x; cyl[1]=y;
type1.cycle=cyl;

type1.vie=lire(tab,0,&l);tab=tab+l;
type1.cad=lire(tab,0,&l);tab=tab+l;// modif int en double????
type1.vit=lire(tab,0,&l);tab=tab+l; printf("\nvit:%d\n",type1.vit);
type1.deg=lire(tab,0,&l);tab=tab+l;
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
int j;
for(i=0;i<V->h;i++){
for(j=0;j<V->l;j++){
printf("%c ",V->visuel[i][j]);// aparence du vaiseau
}
printf("\n");
}

printf("%d\n",V->vit);// vitesse du tire en case / seconde
printf("%f\n",V->cad);// cadence de tire ex: 0.5
printf("%c\n",V->tir);// apparence du tire
printf("%d\n",V->deg);// 			les degats engendre
printf("%d\n",V->vie);// vie par defaut

printf("%d\n",V->lcycle);

for (i=0;i<V->lcycle; i++){
printf("%d ",V->cycle[0][i]);
    }
printf("\n");
for (i=0;i<V->lcycle; i++){
printf("%d ",V->cycle[1][i]);
    }
printf("\n");

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


