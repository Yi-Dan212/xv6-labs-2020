#include "kernel/types.h"
#include "user/user.h"

/**/


int main(int argv,char* argc[]){
    int pipep[2];
    int pipec[2];
    pipe(pipep);
    pipe(pipec);
    char byte[1]={'B'};
    char buf[64];
    int pid=fork();
    if(fork<0){
        close(pipep[0]);
        close(pipep[1]);
        close(pipec[1]);
        close(pipec[0]);
        exit(1);
    }
    if(pid==0){
        close(pipep[1]);
        close(pipec[0]);
        int num=read(pipep[0],buf,sizeof(buf));
        if(num<=0)exit(1);
        close(pipep[0]);
        printf("%d: received ping\n",getpid());
        num=write(pipec[1],byte,1);
        if(num<=0)exit(1);
        close(pipec[1]);
        exit(0);
    }
    else{
        close(pipep[0]);
        close(pipec[1]);
        int num=write(pipep[1],byte,1);
        if(num<=0)exit(1);
        close(pipep[1]);
        num=read(pipec[0],buf,sizeof(buf));
        if(num<=0)exit(1);
        close(pipec[0]);
        printf("%d: received pong\n",getpid());
        exit(0);
    }
}