#include<stdio.h>
#include<stdlib.h>

 #include <sys/types.h>
       #include <unistd.h>

#include<stropts.h>
#include<poll.h>


#include "fonction.h"
typedef struct Tire Tire;
struct Tire {
	int x;
	int y;
	double cad;// cadance
	int dega;// vie en moin
	char visu;
};

void tire(int x,int y,Type A,Tire* t){// Ajoute un tire en fonction de la
int i=0;
	while(i<100 && t[i].cad!=0){
		i++;
	}

	if (i<100){
		Tire T;
		T.x=x;
		T.y=y;
		T.cad=A.cad;
		T.dega=A.deg;
		T.visu=A.tir;
		t[i]=T;
	}
}

void AfficheTire (char** cadre, Tire* t, Vaisseau* vais,long time){// affiche le tire // retire la vie s'il touche un vaiseau// fin du parcour du tire// depalcement du tire.
int i=0;int j;int x=t[i].x; int y=t[i].y;
	while(i<100){
	cadre[y][x]=t[i].visu;
	j=0;
		while( !(vais[j].x<0) ){
			if(vais[j].vie>0 && x>=vais[j].x && x<=vais[j].x+vais[j].cat.l && y>=vais[j].y && y<=vais[j].y+vais[j].cat.h){
			 	vais[j].vie=vais[j].vie-t[i].dega;
				t[i].cad=0;
			 }else{
				if( (int)(time*t[i].cad)%2==0 ){
					t[i].y=y-1;
					if (t[i].y<=0)t[i].cad=0;
				}
				}
			j++;
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



