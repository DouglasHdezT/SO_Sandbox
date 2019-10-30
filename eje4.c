#include <unistd.h> 
#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include<pthread.h>

pthread_mutex_t lock;


int main(){
    int n=12;
    int* ppos= (int*) malloc(sizeof(int));
    int pids[n]; 
    int pipi = getpid();
    int  cpid=0, cpos=-1;
    *ppos = 0; 

    for (int i = 0; i < n; i++)
    {
       int child=fork();
       if(child==0){
            pids[i] = getpid();
            cpid=getpid();
            cpos=i;
            break;
        }
        if(pipi == getpid()){
            wait(NULL);

        }

    }
    if(pipi == getpid()){
        for(int i = 0; i < n; i++){
            printf("%d ->", pids[i]);
        }
    }

    while(1){
        printf("%d\n", cpos);
        if(*ppos == cpos){
            printf("Soy el hijo %d: %d \n",*ppos,getpid());
            *ppos++;
            if(*ppos == n){
                *ppos=0;
            }
        }
    }

    /* while(1){
        if(getpid()!=pipi){
            printf("Soy el hijo %d \n",getpid());
        }
    } */
    /* int child=fork();
    int child2=-1;
    if(child>0){
        child2=fork();
    }
    if(child==0){
        printf("Soy el hijo 1 %d \n",getpid());
    }
    if(child2==0){
        printf("Soy el hijo 2 %d \n",getpid());
    } */
    
    return 0;
}