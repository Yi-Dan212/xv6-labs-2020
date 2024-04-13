#include "../kernel/types.h"
#include "user.h"
#define size sizeof(int)




void prime(int lp){
    int left;
    int ret=read(lp,&left,size);
    if(ret<=0){
        close(lp);
        exit(1);
    }
    printf("prime %d\n",left);
    int p[2];
    pipe(p);
    int pid=fork();
    if(pid<0){
        printf("fork erro\n");
        exit(1);
    }
    if(pid==0){
        close(p[1]);
        prime(p[0]);
    }
    close(p[0]);
    if(pid>0){
        int num;
        while(read(lp,&num,size)==size){
        if(num%left==0)continue;
        write(p[1],&num,size);
        }
        close(lp);
        close(p[1]);
        wait(0);
    }
    exit(0);
}




int main(int argv,char* argc[]){
    int p[2];
    pipe(p);
    for(int i=2;i<=35;i++){
        write(p[1],&i,size);
    }
    close(p[1]);
    if(fork()==0){
        prime(p[0]);
    }
    else {
        close(p[0]);
        close(p[1]);
        wait(0);
    }
    exit(0);
}