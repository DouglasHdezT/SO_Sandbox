#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    int n=0;
    printf("Ingrese la cantidad de maxima de procesos: ");
    scanf("%d", &n);
    printf("PID: %d \n",getpid());
    
    
    for (int i = 0; i < n; i++)
    {
        int child1 = fork(); //<- retornara > 0 en el papa

        if(child1>0){
            wait(NULL);
        }

        if(child1 == 0)
        {   
            for(int j = 0 ; j <= i;j++){
                printf("\t");    
            }
            printf("PID: %d \n",getppid());
            for(int j = 0 ; j <= i;j++){
                printf("\t");    
            }
            printf("PID: %d \n",getpid());
        }
    }
    
    
    
}
