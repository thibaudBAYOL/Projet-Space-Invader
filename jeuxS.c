#include<stdio.h>
#include<stdlib.h>

 #include <sys/types.h>
       #include <unistd.h>

#include<stropts.h>
#include<poll.h>

int main(int argv, char*argc){

char buf[1];
//////////////////////////////////////POLL
struct pollfd fds[1];
int time=500;
int ret;

fds[0].fd=0;
fds[0].events=POLLIN;

int a=0;int b=0;
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



