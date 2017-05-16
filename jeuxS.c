#include<stdio.h>
#include<stdlib.h>

 #include <sys/types.h>
       #include <unistd.h>

#include<stropts.h>
#include<poll.h>


#include "fonction.h"









int won(Vaisseau* V){
int i = 0;
	while(V[i].x!=-5 || V[i].cat.vie<0){
		i++;
	}	
if (V[i].x==-5) return 0;
return 1;
}




int M=0;
do{

//.....(M)
/*  */






M++;
}while(V[M]!=NULL);




void majJoueur(Vaisseau***corde, int x, int w,Vaisseau*jeu){
int i,j;
for(i=x-1;x<=i+1;i++){
	for(j=w.ws.raw-2 ;j<=W.ws.row-2 -1;j++){
		cord[j][i]=Jeu;
	}
}

}


typedef struct Tire Tire;
struct Tire {
	int libe;
	int perso;
	int x;
	int y;
	int dega;// vie en moin
	double vit;
	char visu;
	double last;
};

void tire(int x,int y,Vaiseau* A,int perso,Tire* t,double time){// Ajoute un tire en fonction de la

	if ( (time-(A->cadOld))>=1./(A->cat.cad)){

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
				T.dega=A.deg;
				T.visu=A.tir;
				T.vit=(1/A.vit);
				T.last=time;
				t[i]=T;
			}
	A->cadOld=time;
	}
}

void Majtire (char** cadre,Vaiseau *** info, Tire* t,double time){// affiche le tire // retire la vie s'il touche un vaiseau// fin du parcour du tire// depalcement du tire.
int i;int j;int x; int y;
	for(i=0;i<100;i++){	
		if (t[i].libre==0){
		x=t[i].x; 
		y=t[i].y;
			if( time-(t[i].last)>=(t[i].vit) ){
					if (t[i].perso==1){
						t[i].y=y-1;
					}else{
						t[i].y=y+1;
					}
					t[i].last=time;
					if (t[i].y<=0/*gérer le haut du tableau avec w*/)t[i].libre=1;
			}
			x=t[i].x; 
			y=t[i].y;
			if(info[x][y]!=NULL){
			 	info[y][x]->vie=info[x][y]->vie-t[i].dega;
				t[i].libre=1;
			 }else{
				cadre[y][x]=t[i].visu;
			}
		}
	}

}




int main(int argv, char**argc){

char buf[1];
//////////////////////////////////////POLL
struct pollfd fds[1];
int time=500;
int ret;

fds[0].fd=0;
fds[0].events=POLLIN;


do{


ret = poll(fds,1,time);
if (ret>0){
	if (fds[0].revents & POLLIN){
	read(0,buf,1);

	}
}

}while(buf[0]!='Q');
//////////////////////////////////////POLL

return 0;
}



