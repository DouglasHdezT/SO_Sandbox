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
    int pipi = getpid();
    int  cpid=0, cpos=-1;
    *ppos = 0; 
	
	int child;
	
    for (int i = 0; i < n; i++)
    {
       child=fork();

       if(child==0){
           printf("Hijo %d pid: %d \n",i,getpid());
    	   break;
        }
        if(child>0){
        	wait(NULL);
        }

    }
    

	
    
    return 0;
}
