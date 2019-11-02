#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <pthread.h>
#define N  4

pthread_t tids[N];
int n = N;
int gCont=0;

int step = 1;

typedef struct myThread{
	pthread_t* tid;
	int index;
} MT;


void handle_sighup(int signum){
    
    if(signum == 4){
        //printf("Soy una senal de: %d\n", getpid());
        return;
    }
    if(signum == 5){
        //printf("Soy el tata con una senal de: %d\n", getpid());
        return;
    }
    if(signum==2){
		step = step * -1;
    }
    if(signum==15){
       exit(0);
    }
}

void *myThreadFun(void *vargp) 
{ 
    // Store the value argument passed to this thread 
    while(1){
		pause();
		sleep(2);	
		printf("Soy el hilo %d con el tid: %ld \n",((MT*)vargp)->index,pthread_self());
		kill(getpid(),4);
	}
} 

int main(){
    signal(SIGTRAP, handle_sighup);
    signal(SIGILL, handle_sighup);
    signal(SIGTERM, handle_sighup);
    signal(SIGINT, handle_sighup);
    
    
    for(int i=0;i<n;i++){
        pthread_t tid; 
		MT* myThread = (MT *)malloc(sizeof(MT));
    	myThread->tid = &tid;
    	myThread->index = i;
        pthread_create(&tid, NULL, myThreadFun, (void *)myThread ); 
        tids[i]=tid;
            
    }
    
    /*for(int i =0;i<N;i++){
    	printf("%ld \n",tids[i]);
    }*/
    while(1){
    	pthread_kill(tids[gCont], 4);
    	pause();
    	gCont = gCont + step;
    	if(gCont == N){
    		gCont =0;
    	}
    	if(gCont < 0){
    		gCont =N-1;
    	}
    }

 	pthread_exit(NULL); 
    return 0;
}
