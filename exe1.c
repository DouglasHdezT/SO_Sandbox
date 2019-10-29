#include <unistd.h> 
#include <stdio.h> 
#include <sys/types.h>
#include <sys/wait.h>

int main(){
    
    printf("%d \n",getpid());
    
    int n = 2;
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
            printf("%d \n",getppid());
            for(int j = 0 ; j <= i;j++){
                printf("\t");    
            }
            printf("%d \n",getpid());
        }
    }
    
    
    
}
